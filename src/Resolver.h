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
#ifndef RESOLVER_H_
#define RESOLVER_H_

#include "String.h"
#include <vector>

namespace Riak {

class Client;
class Object;
class Bucket;

class Resolver {
public:
	Resolver(Client &client, const Bucket& bucket) : client(client), bucket(bucket) {}
	virtual ~Resolver() {}
	virtual const String resolve(Object& object, const std::vector<String> &vtags) = 0;
protected:
	const Bucket& bucket;
	Client& client;
};

} /* namespace Riak */
#endif /* RESOLVER_H_ */
