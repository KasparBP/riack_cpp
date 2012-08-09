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
	this->value = 0;
	this->valueLength = 0;
}

Object::~Object() {
	reset();
}

void Object::setContentType(const String& contentType) {
	this->contentType = contentType;
}

void Object::setContentEncoding(const String& contentEncoding) {
	this->contentEncoding = contentEncoding;
}

void Object::reset() {
	if (value != 0 && valueLength > 0) {
		delete [] value;
	}
	value = 0;
	valueLength = 0;
}

void Object::setValue(uint8_t *value, size_t valueLength) {
	reset();
	this->valueLength = valueLength;
	this->value = new uint8_t[valueLength];
	memcpy(this->value, value, valueLength);
}

bool Object::fetch() {
	return false;
}

bool Object::store() {
	struct RIACK_CLIENT* riackClient;
	struct RIACK_OBJECT obj, returnedObj;
	struct RIACK_CONTENT content;
	memset(&obj, 0, sizeof(obj));
	memset(&returnedObj, 0, sizeof(returnedObj));
	memset(&content, 0, sizeof(content));
	content.content_type = contentType.getAsRiackString();
	content.content_encoding = contentEncoding.getAsRiackString();
	content.data = this->value;
	content.data_len = this->valueLength;

	obj.bucket = bucket->getName().getAsRiackString();
	obj.key = key.getAsRiackString();
	obj.content_count = 1;
	obj.content = &content;
	riackClient = bucket->getClient()->getRiackClient();
	if (riack_put(riackClient, obj, &returnedObj, 0) == RIACK_SUCCESS) {
		// TODO read back value from returnedObj
		riack_free_object(riackClient, &returnedObj);
		return true;
	}

	return false;
}

} /* namespace Riak */
