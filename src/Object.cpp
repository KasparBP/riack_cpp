/*
 * Object.cpp
 *
 *  Created on: 21/07/2012
 *      Author: kaspar
 */

#include "Object.h"
#include "Bucket.h"

namespace Riak {

Object::Object(Bucket *bucket) {
	this->bucket = bucket;
}

Object::~Object() {
}

} /* namespace Riak */
