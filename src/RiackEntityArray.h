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

#ifndef RIACKENTITYARRAY_H_
#define RIACKENTITYARRAY_H_

#include <vector>
#include <stdexcept>
#include "RiackCppDefines.h"
#include "RiackEntity.h"

namespace Riak {

#define RIACK_ENTITY_ARRAY_INCREMENT 5

template <typename Type, class EntityClass = RiackEntity<Type> >
class RiackEntityArray {
public:
	RiackEntityArray() : entityCount(0), arrayLength(0), array(NULL) {
	}

	virtual ~RiackEntityArray() {
		if (array != NULL && arrayLength > 0) {
			delete [] array;
		}
	}

	void addEntity(const EntityClass& entity) {
		entities.push_back(entity);
		addEntityToArray(entity);
	}

	size_t count() const {
		return entityCount;
	}

	Type* getAsRiackEntityArray() const {
		return array;
	}

	void clear() {
		if (array != NULL && arrayLength > 0) {
			delete [] array;
			array = NULL;
		}
		entityCount = arrayLength = 0;
		entities.clear();
	}

	const EntityClass &getEntityAt(size_t index) {
		if (index >= count()) {
			throw std::out_of_range("Index out of bounds in RiackEntityArray::getEntityAt");
		}
		return entities[index];
	}
private:
	void addEntityToArray(const EntityClass& entity) {
		++entityCount;
		if (entityCount > arrayLength) {
			if (array != NULL && arrayLength > 0) {
				delete [] array;
			}
			arrayLength += RIACK_ENTITY_ARRAY_INCREMENT;
			array = new Type[arrayLength];
			for (size_t i=0; i<entityCount-1; ++i) {
				array[i] = entities[i].getAsRiackEntity();
			}
		}
		array[entityCount-1] = entity.getAsRiackEntity();
	}

	std::vector<EntityClass> entities;
	size_t entityCount;
	size_t arrayLength;
	Type* array;
};


} /* namespace Riak */
#endif /* RIACKENTITYARRAY_H_ */
