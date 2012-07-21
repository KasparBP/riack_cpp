/*
 * Client.cpp
 *
 *  Created on: 21/07/2012
 *      Author: kaspar
 */

#include "Client.h"

namespace Riak {

Client::Client(const std::string& host, int port) {
	this->host = host;
	this->port = port;
	connected = false;

	client = ::riack_new_client(0);
}

Client::~Client() {
	riack_free(client);
}

} /* namespace Riak */
