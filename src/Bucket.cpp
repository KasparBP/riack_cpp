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

namespace Riak {

Bucket::Bucket(Client *client, const String& name) {
	this->client = client;
	this->name = name;
}

Bucket::~Bucket() {
}

Client* Bucket::getClient() {
	return client;
}

const String& Bucket::getName() const {
	return name;
}

std::auto_ptr<Object> Bucket::fetchObject(const String &key) {
	// TODO Check connected
	std::auto_ptr<Object> result = std::auto_ptr<Object>(new Object(this, key));
	if (!result->fetch()) {
	}
	return result;
}

} /* namespace Riak */
