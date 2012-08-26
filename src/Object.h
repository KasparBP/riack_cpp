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
#include "Content.h"

namespace Riak {

class Bucket;

class Object : public Content {
public:
	typedef enum {
		fetchedOk,
		fetchedConflicted
	} FetchResult;

	Object(Bucket *bucket, const String& key);
	virtual ~Object();

	FetchResult fetch();
	void store();
	void burry(); // TODO Rename

	size_t getSiblingCount();
	const Content& getSibling(size_t index);
	void chooseSibling(size_t index);
private:
	Bucket *bucket;
	String key;
	bool conflicted;
	std::vector<Content> siblings;
};

} /* namespace Riak */
#endif /* RIACKCPP_OBJECT_H_ */
