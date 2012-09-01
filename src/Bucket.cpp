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
#include "Bucket.h"
#include "Client.h"
#include "Object.h"
#include <string.h>

namespace Riak {

Bucket::Bucket(Client& client, const String& name) : nVal(3), allowMult(false) {
	this->name = name;
	getBucketProperties(client);
}

Bucket::~Bucket() {
}

void Bucket::getBucketProperties(Client& client) {

}

const String& Bucket::getName() const {
	return name;
}

} /* namespace Riak */
