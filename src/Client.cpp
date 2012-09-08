/*
   Copyright 2012 Trifork A/S
   Author: Kaspar Pedersen

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include "Client.h"
#include "Object.h"
#include "Bucket.h"
#include "RiakExceptions.h"
#include <memory.h>

namespace Riak {

Client::Client(const std::string& host, int port) {
	this->host = host;
	this->port = port;
	connected = false;

	client = ::riack_new_client(0);
}

Client::~Client() {
	riack_free(client);
}
struct RIACK_CLIENT *Client::getRiackClient()
{
	return client;
}

bool Client::isConnected()
{
	return connected;
}

bool Client::connect()
{
	int status = connected ?
			riack_reconnect(client) :
			riack_connect(client, host.c_str(), port, 0);

	connected = (status == RIACK_SUCCESS);
	return connected;
}

bool Client::ping()
{
	if (connected) {
		if (riack_ping(client) == RIACK_SUCCESS) {
			return true;
		}
	}
	return false;
}

void Client::applyBucketProperties(const Bucket& bucket) {
	int riackResult = riack_set_bucket_props(getRiackClient(), bucket.getName().getAsRiackString(), bucket.getNVal(), bucket.getAllowMult() ? 1 : 0);
	if (riackResult != RIACK_SUCCESS) {
		ThrowRiackException::throwRiackException(*this, riackResult);
	}
}

void Client::fetchBucketProperties(Bucket& bucket) {
	uint32_t nVal = 3;
	uint8_t allowMult = 0;
	int riackResult = riack_get_bucket_props(getRiackClient(), bucket.getName().getAsRiackString(), &nVal, &allowMult);
	if (riackResult != RIACK_SUCCESS) {
		ThrowRiackException::throwRiackException(*this, riackResult);
	}
	bucket.setAllowMult(allowMult > 0);
	bucket.setNVal(nVal);
}

void Client::store(const Bucket& bucket, const String& key, const Object& object) {
	struct RIACK_OBJECT obj, returnedObj;
	struct RIACK_CONTENT riackContent;
	struct RIACK_PUT_PROPERTIES props;
	int riackResult;

	memset(&obj, 0, sizeof(obj));
	memset(&returnedObj, 0, sizeof(returnedObj));
	memset(&riackContent, 0, sizeof(riackContent));
	memset(&props, 0, sizeof(props));

	object.setToRiackContent(riackContent);

	obj.bucket = bucket.getName().getAsRiackString();
	obj.key = key.getAsRiackString();
	obj.content_count = 1;
	obj.content = &riackContent;
	obj.vclock.clock = (uint8_t*)object.getVClock().getAsRiackString().value;
	obj.vclock.len = object.getVClock().getStringLength();
	riackResult = riack_put(getRiackClient(), obj, &returnedObj, &props);
	if (riackResult == RIACK_SUCCESS) {
		riack_free_object(getRiackClient(), &returnedObj);
	} else {
		ThrowRiackException::throwRiackException(*this, riackResult);
	}
}

void Client::del(const Bucket& bucket, Object& object) {
	int riackResult;
	riackResult = riack_delete(getRiackClient(), bucket.getName().getAsRiackString(),
			object.getKey().getAsRiackString(), 0);
	if (riackResult != RIACK_SUCCESS) {
		ThrowRiackException::throwRiackException(*this, riackResult);
	}
}

bool Client::fetch(const Bucket& bucket, Object &object) {
	return fetch(object, bucket, object.getKey());
}

std::auto_ptr<Object> Client::fetch(const Bucket& bucket, const String& key) {
	std::auto_ptr<Object> result = std::auto_ptr<Object>(new Object(key));
	if (!fetch(*result, bucket, key)) {
		result.reset(0);
	}
	return result;
}

bool Client::fetch(Object &object, const Bucket& bucket, const String& key) {
	bool result = false;
	size_t contentCount;
	struct RIACK_GET_PROPERTIES props;
	struct RIACK_GET_OBJECT getResult;

	memset(&props, 0, sizeof(props));
	memset(&getResult, 0, sizeof(getResult));

	int riackResult = riack_get(getRiackClient(), bucket.getName().getAsRiackString(), key.getAsRiackString(), &props, &getResult);
	if (riackResult == RIACK_SUCCESS) {
		contentCount = getResult.object.content_count;
		if (contentCount > 1) {
			ConflictedObjectsVector conflictedObjects;
			for (size_t i=0; i<contentCount; ++i) {
				Object currentObject(key);
				currentObject.setFromRiackContent(getResult.object.content[i], true);
				currentObject.setVClock(getResult.object.vclock.clock,
					getResult.object.vclock.len);
				conflictedObjects.push_back(currentObject);
			}
			riack_free_get_object(getRiackClient(), &getResult);
			throw ConflictedException(bucket.getName(), key, conflictedObjects);
		} else if (contentCount > 0) {
			object.setFromRiackContent(getResult.object.content[0], true);
			object.setVClock(getResult.object.vclock.clock, getResult.object.vclock.len);
			result = true;
		}
		riack_free_get_object(getRiackClient(), &getResult);
	}  else {
		ThrowRiackException::throwRiackException(*this, riackResult);
	}
	return result;
}

Object Client::resolve(Resolver& resolver, ConflictedException& exception) {
	ConflictedObjectsVector objects = exception.getConflictedObjects();
	return resolver.resolve(objects);
}

} /* namespace Riak */
