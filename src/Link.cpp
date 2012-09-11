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

#include "Link.h"

namespace Riak {

#define ARRAY_INC_SIZE 5

Link::Link(const struct RIACK_LINK &link) {
	tag = String(link.tag);
	bucket = String(link.bucket);
	key = String(link.key);
}

Link::~Link() {
}

struct RIACK_LINK Link::getAsRiackEntity() const {
	struct RIACK_LINK result;
	result.bucket = bucket.getAsRiackString();
	result.key = key.getAsRiackString();
	result.tag = tag.getAsRiackString();
	return result;
}

/////////////////////////////////////
// LinkArray
/*
LinkArray::LinkArray() :
	linkArray(NULL), linkCount(0), arrayLength(0)  {
}

LinkArray::~LinkArray() {
	if (linkArray && arrayLength > 0) {
		delete [] linkArray;;
	}
}

void LinkArray::addLink(const Link& link) {
	links.push_back(link);
}

void LinkArray::addToArray(const Link& link) {
	linkCount++;
	if (linkCount > arrayLength) {
		delete [] linkArray;
		arrayLength += ARRAY_INC_SIZE;
		linkArray = new struct RIACK_LINK[arrayLength];
		for (size_t i=0; i<linkCount; ++i) {
			linkArray[i] = links[i].getAsRiackEntity();
		}
	}
}
*/
} /* namespace Riak */
