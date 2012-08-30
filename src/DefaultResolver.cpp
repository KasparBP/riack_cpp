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
#include "DefaultResolver.h"
#include "Object.h"
#include "Client.h"

namespace Riak {

DefaultResolver::DefaultResolver(Client &client, const Bucket& bucket) :
		Resolver(client, bucket) {
}

std::auto_ptr<Object> DefaultResolver::chooseBestObject(std::auto_ptr<Object> obj1,
		std::auto_ptr<Object> obj2) {
	// TODO
	return obj2;
}

const String DefaultResolver::resolve(Object& object, const std::vector<String> &vtags) {
	std::vector<String>::const_iterator iter;
	std::auto_ptr<Object> currentlyChoosenObject;
	for (iter = vtags.begin(); iter != vtags.end(); ++iter) {
		const String &currentVtag = *iter;
		std::auto_ptr<Object> currentObject = client.fetch(bucket, object.getKey(), &currentVtag);
		if (currentlyChoosenObject.get() != NULL) {
			currentlyChoosenObject = chooseBestObject(currentlyChoosenObject, currentObject);
		} else {
			currentlyChoosenObject = currentObject;
		}
	}
	if (currentlyChoosenObject.get() == NULL) {
		// TODO Throw bad exception
	}
	object = *currentlyChoosenObject;
	return currentlyChoosenObject->getVtag();
}

} /* namespace Riak */
