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
#ifndef RIACKCPP_BUCKET_H_
#define RIACKCPP_BUCKET_H_

#include "String.h"
#include <memory>

namespace Riak {

class Client;
class Object;

class Bucket {
public:
	Bucket(Client& client, const String& name);
	virtual ~Bucket();

	const String& getName() const;

	uint32_t getNVal() const;
	bool getAllowMult() const;

	void setNVal(uint32_t nVal);
	void setAllowMult(bool allowMult);
private:
	String name;

	uint32_t nVal;
	bool allowMult;
};

} /* namespace Riak */
#endif /* RIACKCPP_BUCKET_H_ */
