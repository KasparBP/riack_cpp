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

#ifndef RIACKCPP_OBJECT_H_
#define RIACKCPP_OBJECT_H_

#include <vector>
#include "RiackCpp.h"
#include "String.h"

namespace Riak {

class Object {
	friend void swap(Object& first, Object& second) throw();
public:
	Object(const String& key);
	virtual ~Object();

	const String& getKey() const;

	Object& operator=(Object other);

	void setContentType(const String& contentType);
	void setContentEncoding(const String& contentEncoding);
	void setVtag(const String& vtag);
	void setValue(uint8_t *value, size_t valueLength);

	void setVClock(uint8_t *clockData, size_t clockLen);

	void setFromRiackContent(const struct RIACK_CONTENT& content, bool hasData);

	const String& getContentType() const;
	const String& getContentEncoding() const;
	const String& getVtag() const;

	const String& getVClock() const;

	const uint8_t* getValue() const;
	const size_t getValueLength() const;

	uint8_t* getValue();
	size_t getValueLength();
private:
	void reset();

	String vClock;

	String key;

	String contentType;
	String contentEncoding;
	String vtag;

	size_t valueLength;
	uint8_t *value;
};

typedef std::auto_ptr<Object> ObjectAutoPtr;

} /* namespace Riak */
#endif /* RIACKCPP_OBJECT_H_ */
