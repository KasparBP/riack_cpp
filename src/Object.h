/*
 * Object.h
 *
 *  Created on: 21/07/2012
 *      Author: kaspar
 */

#ifndef RIACKCPP_OBJECT_H_
#define RIACKCPP_OBJECT_H_

namespace Riak {

class Bucket;

class Object {
public:
	Object(Bucket *bucket);
	virtual ~Object();
private:
	Bucket *bucket;
};

} /* namespace Riak */
#endif /* RIACKCPP_OBJECT_H_ */
