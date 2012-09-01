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

#ifndef RIACKCPP__STRING_H__
#define RIACKCPP__STRING_H__

#include "RiackCpp.h"
#include <string>

namespace Riak {

class String {
	friend void swap(String& first, String& second) throw();
public:
	String();
	String(const std::string& str);
	String(const String& str);
	String(const RIACK_STRING& str);
	String(const char* str);
	String(const char* str, size_t length);
	virtual ~String();

	String& operator=(String other);

	std::string toStdString() const;

	void setValue(const std::string& value);
	const RIACK_STRING& getAsRiackString() const;
	const size_t getStringLength() const;
private:
	void initWith(const char* data, size_t dataLen);
	void reset();
	RIACK_STRING riackString;
};

} /* namespace Riak */
#endif /* RIACKCPP__STRING_H__ */
