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

#ifndef METADATA_H_
#define METADATA_H_

#include "String.h"
#include "RiackEntity.h"

namespace Riak {
class Metadata : public RiackEntity<struct RIACK_PAIR> {
	friend void swap(Metadata& first, Metadata& second) throw();
public:
	Metadata(const Metadata& other);
	Metadata(const String &key);
	Metadata(const String &key, const String &value);
	Metadata(const String &key, const uint8_t* value, size_t valueLength);
	Metadata(const struct RIACK_PAIR& pair);
	virtual ~Metadata();

	Metadata& operator=(Metadata other);
	bool operator==(const Metadata &other) const;
	bool operator!=(const Metadata &other) const;

	void setValue(const uint8_t* value, size_t length);

	const String& getKey() const;
	size_t getLength() const;
	const uint8_t* getValue() const;

//	struct RIACK_PAIR getAsRiackPair() const;
	virtual struct RIACK_PAIR getAsRiackEntity() const;
private:
	void reset();
	String key;

	uint8_t* value;
	size_t valueLength;
};

} /* namespace Riak */
#endif /* METADATA_H_ */
