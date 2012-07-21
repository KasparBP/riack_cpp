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

#include "RiackCpp.h"
#include "String.h"
#include "Content.h"

namespace Riak {

class Bucket;

class Object {
public:
	Object(Bucket *bucket, const String& key);
	virtual ~Object();

	void setValue(uint8_t *value, size_t valueLength);
	bool store();

	void setContentType(const String& contentType);
private:
	void reset();
	Bucket *bucket;
	String key;
	String contentType;

	size_t valueLength;
	uint8_t *value;
};

} /* namespace Riak */
#endif /* RIACKCPP_OBJECT_H_ */
