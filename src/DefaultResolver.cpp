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

Object& DefaultResolver::chooseBestObject(Object& obj1,
		Object& obj2) {
	// TODO
	return obj2;
}

Object& DefaultResolver::resolve(ConflictedObjectsVector& conflictedObjects) {
	ConflictedObjectsVector::iterator iter;
	Object *currentlyChoosenObject = NULL;
	for (iter = conflictedObjects.begin(); iter != conflictedObjects.end(); ++iter) {
		if (currentlyChoosenObject != NULL) {
			currentlyChoosenObject = &chooseBestObject(*currentlyChoosenObject, *iter);
		} else {
			currentlyChoosenObject = &*iter;
		}
	}
	return *currentlyChoosenObject;
}

} /* namespace Riak */
