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

void swap(Object& first, Object& second) throw()
{
	std::swap(first.value, first.value);
	std::swap(first.valueLength, first.valueLength);
	std::swap(first.contentEncoding, first.contentEncoding);
	std::swap(first.contentType, first.contentType);
	std::swap(first.vtag, first.vtag);
	std::swap(first.key, first.key);
}


Object::Object(const String& key) :
	key(key), value(0), valueLength(0) {
}

Object::~Object() {
}


Object& Object::operator=(Object other) {
	std::swap(*this, other);
	return *this;
}

void Object::setContentType(const String& contentType) {
	this->contentType = contentType;
}

void Object::setContentEncoding(const String& contentEncoding) {
	this->contentEncoding = contentEncoding;
}

void Object::setVtag(const String& vtag) {
	this->vtag = vtag;
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

void Object::setFromRiackContent(const struct RIACK_CONTENT& content, bool hasData) {
	contentEncoding = content.content_encoding;
	contentType = content.content_type;
	vtag = content.vtag;
	if (hasData) {
		setValue(content.data, content.data_len);
	}
}

const String& Object::getContentType() const {
	return contentType;
}

const String& Object::getContentEncoding() const {
	return contentEncoding;
}

const String& Object::getVtag() const {
	return vtag;
}

const uint8_t* Object::getValue() const {
	return value;
}

const size_t Object::getValueLength() const {
	return valueLength;
}

uint8_t* Object::getValue() {
	return value;
}

size_t Object::getValueLength() {
	return valueLength;
}

const String& Object::getKey() const {
	return key;
}


} /* namespace Riak */
