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

#include "Metadata.h"
#include <memory.h>
#include <memory>

namespace Riak {

void swap(Metadata& first, Metadata& second) throw() {
	std::swap(first.key, second.key);
	std::swap(first.value, second.value);
	std::swap(first.valueLength, second.valueLength);
}

Metadata::Metadata(const Metadata& other) :
	value(NULL), valueLength(0), key(other.key) {
	setValue(other.value, other.valueLength);
}

Metadata::Metadata(const String &key, const String &value) :
	value(NULL), valueLength(0), key(key) {
	setValue((uint8_t*)value.getAsRiackString().value, value.getStringLength());
}

Metadata::Metadata(const String &key) :
	value(NULL), valueLength(0) {
	this->key = key;
}

Metadata::Metadata(const String &key, const uint8_t* value, size_t valueLength) :
	value(NULL), valueLength(0), key(key) {
	setValue(value, valueLength);
}

Metadata::Metadata(const struct RIACK_PAIR& pair) :
	value(NULL), valueLength(0), key(pair.key) {
	if (pair.value_present) {
		setValue(pair.value, pair.value_len);
	}
}

Metadata::~Metadata() {
	reset();
}

void Metadata::reset() {
	if (value != NULL && valueLength > 0) {
		delete [] value;
		value = NULL;
	}
	valueLength = 0;
}

void Metadata::setValue(const uint8_t* value, size_t length) {
	reset();
	valueLength = length;
	if (length > 0) {
		this->value = new uint8_t[valueLength];
		if (this->value != NULL) {
			memcpy(this->value, value, valueLength);
		}
	}
}

Metadata& Metadata::operator=(Metadata other) {
	swap(*this, other);
	return *this;
}

bool Metadata::operator==(const Metadata &other) const {
	if ((other.key == key) && (other.valueLength == valueLength)) {
		return memcmp(other.value, value, valueLength) == 0;
	}
	return false;
}

bool Metadata::operator!=(const Metadata &other) const {
	return !(*this == other);
}

const String& Metadata::getKey() const {
	return key;
}

size_t Metadata::getLength() const {
	return valueLength;
}

const uint8_t* Metadata::getValue() const {
	return value;
}

struct RIACK_PAIR Metadata::getAsRiackPair() const {
	struct RIACK_PAIR result;
	result.key = key.getAsRiackString();
	if (valueLength > 0) {
		result.value_present = 1;
		result.value = value;
		result.value_len = valueLength;
	} else {
		result.value_present = 0;
	}

	return result;
}

} /* namespace Riak */
