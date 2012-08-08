
#include "RiakTestCase.h"
#include <stdio.h>

namespace Riak {

RiakTestCase::RiakTestCase(const std::vector<std::string> &arguments)
	: TestCase(arguments)
{
	int port;
	std::string ip = arguments[1];

	RiakCpp::init();

	sscanf(arguments[2].c_str(), "%d", &port);
	client = std::auto_ptr<Client>(new Client(ip, port));
}

RiakTestCase::~RiakTestCase()
{
	// Destroy client before calling cleanup
	client.reset(0);
	RiakCpp::cleanup();
}

Client& RiakTestCase::getClient() {
	return *client;
}

} /* namespace Riak */
