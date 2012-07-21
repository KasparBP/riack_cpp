/*
 * Client.h
 *
 *  Created on: 21/07/2012
 *      Author: kaspar
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
extern "C" {
#include <riack.h>
}

namespace Riak {

class Client {
public:
	Client(const std::string& host, int port);
	virtual ~Client();
private:
	std::string host;
	int port;
	bool connected;

	struct RIACK_CLIENT *client;
};

} /* namespace Riak */
#endif /* CLIENT_H_ */
