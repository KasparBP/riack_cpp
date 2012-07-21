/*
 * Bucket.h
 *
 *  Created on: 21/07/2012
 *      Author: kaspar
 */

#ifndef RIACKCPP_BUCKET_H_
#define RIACKCPP_BUCKET_H_

namespace Riak {

class Client;

class Bucket {
public:
	Bucket(Client *client);
	virtual ~Bucket();
private:
	Client *client;
};

} /* namespace Riak */
#endif /* RIACKCPP_BUCKET_H_ */
