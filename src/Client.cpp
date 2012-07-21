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

bool Client::connect() {
	if (connected) {
		if (riack_reconnect(client) == RIACK_SUCCESS) {
			return true;
		}
	} else {
		if (riack_connect(client, host.c_str(), port, 0)) {
			return true;
		}
	}
	return false;
}

} /* namespace Riak */
