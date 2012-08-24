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

#include "Content.h"
#include <string.h>

namespace Riak {

Content::Content() {
	this->value = 0;
	this->valueLength = 0;
}

Content::~Content() {
}


void Content::setContentType(const String& contentType) {
	this->contentType = contentType;
}

void Content::setContentEncoding(const String& contentEncoding) {
	this->contentEncoding = contentEncoding;
}

void Content::reset() {
	if (value != 0 && valueLength > 0) {
		delete [] value;
	}
	value = 0;
	valueLength = 0;
}

void Content::setValue(uint8_t *value, size_t valueLength) {
	reset();
	this->valueLength = valueLength;
	this->value = new uint8_t[valueLength];
	memcpy(this->value, value, valueLength);
}

void Content::setFromRiackContent(const struct RIACK_CONTENT& content, bool hasData) {
	contentEncoding = content.content_encoding;
	contentType = content.content_type;
	vtag = content.vtag;
	if (hasData) {
		setValue(content.data, content.data_len);
	}
}

String Content::getContentType() {
	return contentType;
}

String Content::getContentEncoding() {
	return contentEncoding;
}

String Content::getVtag() {
	return vtag;
}

uint8_t* Content::getValue() {
	return value;
}

size_t Content::getValueLength() {
	return valueLength;
}

} /* namespace Riak */
