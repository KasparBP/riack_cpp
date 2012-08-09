
#include "RiakTestCase.h"
#include <stdio.h>

namespace Riak {

#define TEST_BUCKET_NAME "TEST_BUCKET"

RiakTestCase::RiakTestCase(const std::vector<std::string> &arguments)
	: TestCase(arguments)
{
	int port;
	std::string ip = arguments[0];

	RiakCpp::init();

	sscanf(arguments[1].c_str(), "%d", &port);
	client = std::auto_ptr<Client>(new Client(ip, port));
}

RiakTestCase::~RiakTestCase()
{
	// Destroy client before calling cleanup
	client.reset(0);
	RiakCpp::cleanup();
}

const String RiakTestCase::getTestBucketName() const
{
	return String(TEST_BUCKET_NAME);
}

Client& RiakTestCase::getClient()
{
	return *client;
}

} /* namespace Riak */
