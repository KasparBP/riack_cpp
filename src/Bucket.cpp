/*
 * Bucket.cpp
 *
 *  Created on: 21/07/2012
 *      Author: kaspar
 */

#include "Bucket.h"
#include "Client.h"

namespace Riak {

Bucket::Bucket(Client *client) {
	this->client = client;
}

Bucket::~Bucket() {
}

} /* namespace Riak */
