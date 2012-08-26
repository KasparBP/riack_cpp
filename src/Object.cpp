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

#include "Object.h"
#include "Bucket.h"
#include "Client.h"
#include "RiakExceptions.h"
#include <string.h>

namespace Riak {

Object::Object(Bucket *bucket, const String& key) :
	bucket(bucket), key(key), conflicted(true) {
}

Object::~Object() {
}

size_t Object::getSiblingCount() {
	return siblings.size();
}

const Content& Object::getSibling(size_t index) {
	if (index < 0 || index >= siblings.size()) {
		throw std::out_of_range("index");
	}
	return siblings[index];
}

void Object::chooseSibling(size_t index) {
	if (index < 0 || index >= siblings.size()) {
		throw std::out_of_range("index");
	}
	// TODO
}

void Object::burry() {
	struct RIACK_CLIENT* riackClient;
	int riackResult;
	riackClient = bucket->getClient()->getRiackClient();
	riackResult = riack_delete(riackClient, bucket->getName().getAsRiackString(), key.getAsRiackString(), 0);
	if (riackResult == RIACK_ERROR_COMMUNICATION) {
		throw TransientException("Communication error");
	} else if (riackResult == RIACK_ERROR_RESPONSE) {
		throw ResponseError(riackClient->last_error, riackClient->last_error_code);
	} else if (riackResult == RIACK_ERROR_INVALID_INPUT) {
		throw ArgumentsError("Invalid arguments passed to underlying Riack library");
	}
}

Object::FetchResult Object::fetch() {
	size_t contentCount;
	struct RIACK_CLIENT* riackClient;
	struct RIACK_GET_PROPERTIES props;
	struct RIACK_GET_OBJECT getResult;

	memset(&props, 0, sizeof(props));
	memset(&getResult, 0, sizeof(getResult));

	riackClient = bucket->getClient()->getRiackClient();
	// TODO Throw appropriate exception
	if (riack_get(riackClient, bucket->getName().getAsRiackString(),
			key.getAsRiackString(), &props, &getResult) == RIACK_SUCCESS) {
		contentCount = getResult.object.content_count;
		if (contentCount > 1) {
			siblings.empty();
			for (size_t i=0; i<contentCount; ++i) {
				siblings.push_back(Content(getResult.object.content[i]));
			}
			conflicted = true;
		} else if (contentCount > 0) {
			conflicted = false;
			setFromRiackContent(getResult.object.content[0], true);
		}
		riack_free_get_object(riackClient, &getResult);
	}
	return conflicted ? Object::fetchedConflicted : Object::fetchedOk;
}

void Object::store() {
	struct RIACK_CLIENT* riackClient;
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
	riackContent.content_type = getContentType().getAsRiackString();
	riackContent.content_encoding = getContentEncoding().getAsRiackString();
	riackContent.data = getValue();
	riackContent.data_len = getValueLength();

	obj.bucket = bucket->getName().getAsRiackString();
	obj.key = key.getAsRiackString();
	obj.content_count = 1;
	obj.content = &riackContent;
	riackClient = bucket->getClient()->getRiackClient();
	riackResult = riack_put(riackClient, obj, &returnedObj, &props);
	if (riackResult == RIACK_SUCCESS) {
		if (returnedObj.content_count == 1) {
			setFromRiackContent(returnedObj.content[0], (props.return_body_use && props.return_body));
		}
		riack_free_object(riackClient, &returnedObj);
		if (returnedObj.content_count > 1) {
			throw ConflictedException("Object is now conflicted", bucket->getName().toStdString(), key.toStdString());
		}
	} else if (riackResult == RIACK_ERROR_COMMUNICATION) {
		throw TransientException("Communication error");
	} else if (riackResult == RIACK_ERROR_RESPONSE) {
		throw ResponseError(riackClient->last_error, riackClient->last_error_code);
	} else if (riackResult == RIACK_ERROR_INVALID_INPUT) {
		throw ArgumentsError("Invalid arguments passed to underlying Riack library");
	}
}

} /* namespace Riak */
