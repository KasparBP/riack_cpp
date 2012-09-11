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

#ifndef LINK_H_
#define LINK_H_

#include <vector>
#include "RiackCppDefines.h"
#include "RiackEntity.h"
#include "String.h"


namespace Riak {

class Link : public RiackEntity<struct RIACK_LINK> {
public:
	Link(const String& tag, const String& bucket, const String& key) : tag(tag), bucket(bucket), key(key) {}
	Link(const struct RIACK_LINK &link);
	virtual ~Link();

	virtual struct RIACK_LINK getAsRiackEntity() const;
private:
	String tag;
	String bucket;
	String key;
};
/*
class LinkArray {
public:
	LinkArray();
	virtual ~LinkArray();
	void addLink(const Link& link);
private:
	void addToArray(const Link& link);

	std::vector<Link > links;
	struct RIACK_LINK *linkArray;
	size_t linkCount;
	size_t arrayLength;
};
*/
} /* namespace Riak */
#endif /* LINK_H_ */
