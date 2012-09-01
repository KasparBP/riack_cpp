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
#ifndef DEFAULTRESOLVER_H_
#define DEFAULTRESOLVER_H_

#include "Resolver.h"
#include <vector>
#include <memory>

namespace Riak {

class DefaultResolver : public Resolver {
public:
	virtual Object& resolve(ConflictedObjectsVector& conflictedObjects);

protected:
	Object& chooseBestObject(Object& obj1, Object& obj2);
};

} /* namespace Riak */
#endif /* DEFAULTRESOLVER_H_ */
