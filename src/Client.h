/*
 * Client.h
 *
 *  Created on: 21/07/2012
 *      Author: kaspar
 */

#ifndef RIACKCPP_CLIENT_H__
#define RIACKCPP_CLIENT_H__

#include <string>
#include "RiackCpp.h"

namespace Riak {

class Client {
public:
	Client(const std::string& host, int port);
	virtual ~Client();

private:
	bool connect();

	std::string host;
	int port;
	bool connected;

	struct RIACK_CLIENT *client;
};

} /* namespace Riak */

#endif /* RIACKCPP_CLIENT_H__ */
