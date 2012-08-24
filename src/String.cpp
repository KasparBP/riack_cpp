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

#include "String.h"
#include <string.h>
#include <algorithm>

namespace Riak {

void swap(String& first, String& second)
{
	std::swap(first.riackString, second.riackString);
}

String::String()
{
	initWith(0,0);
}

String::String(const std::string& str)
{
	initWith(str.c_str(), str.length());
}

String::String(const String& str)
{
	initWith(str.riackString.value, str.riackString.len);
}

String::String(const char* str)
{
	initWith(str, strlen(str));
}

String::String(const RIACK_STRING& str) {
	initWith(str.value, str.len);
}

String::~String()
{
	reset();
}

String& String::operator=(String other)
{
	swap(*this, other);
	return *this;
}

void String::initWith(const char* data, size_t dataLen)
{
	riackString.len = dataLen;
	if (dataLen > 0) {
		riackString.value = new char [dataLen];
		memcpy(riackString.value, data, dataLen);
	} else {
		riackString.value = 0;
	}
}

void String::reset()
{
	if (riackString.value != 0 && riackString.len > 0) {
		delete [] riackString.value;
	}
	riackString.value = 0;
	riackString.len = 0;
}

void String::setValue(const std::string& value)
{
	reset();
	initWith(value.c_str(), value.length());
}

const RIACK_STRING& String::getAsRiackString() const
{
	return riackString;
}

} /* namespace Riak */
