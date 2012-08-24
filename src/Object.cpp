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
#include <string.h>

namespace Riak {

Object::Object(Bucket *bucket, const String& key) {
	this->bucket = bucket;
	this->key = key;
	this->state = Ok;

	this->contents.push_back(Content());
}

Object::~Object() {
}

ObjectState Object::getState() {
	return state;
}

Content* Object::getContent(size_t index) {
	if (index < 0 || index >= contents.size()) {
		return NULL;
	}
	return &contents[index];
}

bool Object::fetch() {
	return false;
}

bool Object::store() {
	struct RIACK_CLIENT* riackClient;
	struct RIACK_OBJECT obj, returnedObj;
	struct RIACK_CONTENT content;
	struct RIACK_PUT_PROPERTIES props;

	if (getState() != Ok || contents.size() != 1) {
		return false;
	}

	memset(&obj, 0, sizeof(obj));
	memset(&returnedObj, 0, sizeof(returnedObj));
	memset(&content, 0, sizeof(content));
	memset(&props, 0, sizeof(props));
	props.return_head_use = 1;
	props.return_head = 1;
	content.content_type = contents[0].getContentType().getAsRiackString();
	content.content_encoding = contents[0].getContentEncoding().getAsRiackString();
	content.data = contents[0].getValue();
	content.data_len = contents[0].getValueLength();

	obj.bucket = bucket->getName().getAsRiackString();
	obj.key = key.getAsRiackString();
	obj.content_count = 1;
	obj.content = &content;
	riackClient = bucket->getClient()->getRiackClient();
	if (riack_put(riackClient, obj, &returnedObj, &props) == RIACK_SUCCESS) {
		if (returnedObj.content_count == 1) {
			contents[0].setFromRiackContent(returnedObj.content[0], (props.return_body_use && props.return_body));
		} else {
			// TODO conflifted
		}
		riack_free_object(riackClient, &returnedObj);
		return true;
	}
	return false;
}

} /* namespace Riak */
