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

bool Client::isConnected()
{
	return connected;
}

bool Client::connect()
{
	int status = connected ?
			riack_reconnect(client) :
			riack_connect(client, host.c_str(), port, 0);

	connected = (status == RIACK_SUCCESS);
	return connected;
}

bool Client::ping()
{
	if (connected) {
		if (riack_ping(client) == RIACK_SUCCESS) {
			return true;
		}
	}
	return false;
}

} /* namespace Riak */
