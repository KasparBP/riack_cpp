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

void Client::store(const Bucket& bucket, const String& key, const Object& object) {
	struct RIACK_OBJECT obj, returnedObj;
	struct RIACK_CONTENT riackContent;
	struct RIACK_PUT_PROPERTIES props;
	int riackResult;

	memset(&obj, 0, sizeof(obj));
	memset(&returnedObj, 0, sizeof(returnedObj));
	memset(&riackContent, 0, sizeof(riackContent));
	memset(&props, 0, sizeof(props));
	props.return_head_use = 1;
	props.return_head = 1;
	riackContent.vtag = object.getVtag().getAsRiackString();
	riackContent.content_type = object.getContentType().getAsRiackString();
	riackContent.content_encoding = object.getContentEncoding().getAsRiackString();
	riackContent.data = const_cast<uint8_t*>(object.getValue());
	riackContent.data_len = object.getValueLength();

	obj.bucket = bucket.getName().getAsRiackString();
	obj.key = key.getAsRiackString();
	obj.content_count = 1;
	obj.content = &riackContent;
	riackResult = riack_put(getRiackClient(), obj, &returnedObj, &props);
	if (riackResult == RIACK_SUCCESS) {
		riack_free_object(getRiackClient(), &returnedObj);
		if (returnedObj.content_count > 1) {
			std::vector<String> vtags;
			for (size_t i=0; i<returnedObj.content_count; ++i) {
				vtags.push_back(returnedObj.content[i].vtag);
			}
			throw ConflictedException(bucket.getName(), key, vtags);
		}
	} else if (riackResult == RIACK_ERROR_COMMUNICATION) {
		throw TransientException("Communication error");
	} else if (riackResult == RIACK_ERROR_RESPONSE) {
		throw ResponseError(getRiackClient()->last_error, getRiackClient()->last_error_code);
	} else if (riackResult == RIACK_ERROR_INVALID_INPUT) {
		throw ArgumentsError("Invalid arguments passed to underlying Riack library");
	}
}

void Client::del(const Bucket& bucket, Object& object) {
	int riackResult;
	riackResult = riack_delete(getRiackClient(), bucket.getName().getAsRiackString(),
			object.getKey().getAsRiackString(), 0);
	if (riackResult == RIACK_ERROR_COMMUNICATION) {
		throw TransientException("Communication error");
	} else if (riackResult == RIACK_ERROR_RESPONSE) {
		throw ResponseError(getRiackClient()->last_error, getRiackClient()->last_error_code);
	} else if (riackResult == RIACK_ERROR_INVALID_INPUT) {
		throw ArgumentsError("Invalid arguments passed to underlying Riack library");
	}
}

bool Client::fetch(const Bucket& bucket, Object &object) {
	return fetch(object, bucket, object.getKey(), NULL);
}

std::auto_ptr<Object> Client::fetch(const Bucket& bucket, const String& key) {
	std::auto_ptr<Object> result = std::auto_ptr<Object>(new Object(key));
	if (!fetch(*result, bucket, key, NULL)) {
		result.reset(0);
	}
	return result;
}

bool Client::fetch(Object &object, const Bucket& bucket, const String& key, const String *vtag) {
	bool result = false;
	size_t contentCount;
	struct RIACK_GET_PROPERTIES props;
	struct RIACK_GET_OBJECT getResult;

	memset(&props, 0, sizeof(props));
	memset(&getResult, 0, sizeof(getResult));

	// TODO Throw appropriate exception
	if (riack_get(getRiackClient(), bucket.getName().getAsRiackString(),
			key.getAsRiackString(), &props, &getResult) == RIACK_SUCCESS) {
		contentCount = getResult.object.content_count;
		if (contentCount > 1) {
			std::vector<String> vtags;
			for (size_t i=0; i<contentCount; ++i) {
				vtags.push_back(getResult.object.content[i].vtag);
			}
			throw ConflictedException(bucket.getName(), key, vtags);
		} else if (contentCount > 0) {
			object.setFromRiackContent(getResult.object.content[0], true);
			result = true;
		}
		riack_free_get_object(getRiackClient(), &getResult);
	}
	return result;
}

} /* namespace Riak */
