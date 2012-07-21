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

namespace Riak {

String::String() {
	riackString.len = 0;
	riackString.value = 0;
}

String::String(const std::string& str) {
	setValue(str);
}

String::String(const String& str) {
	riackString.len = str.riackString.len;
	riackString.value = new char [str.riackString.len];
	memcpy(riackString.value, str.riackString.value, str.riackString.len);
}

String::~String() {
	reset();
}

void String::reset() {
	if (riackString.value != 0 && riackString.len > 0) {
		delete [] riackString.value;
	}
	riackString.value = 0;
	riackString.len = 0;
}

void String::setValue(const std::string& value) {
	reset();
	if (value.length() > 0) {
		riackString.len = value.length();
		riackString.value = new char[value.length()];
		memcpy(riackString.value, value.c_str(), value.length());
	}
}

const RIACK_STRING& String::getAsRiackString() const {
	return riackString;
}

} /* namespace Riak */
