
#include "ConnectionTest.h"

namespace Riak {

std::string ConnectionTest::name = "connection";

ConnectionTest::ConnectionTest(const std::vector<std::string> &arguments) : RiakTestCase(arguments)
{}

ConnectionTest::~ConnectionTest() {

}

int ConnectionTest::runTest()
{
	if (!getClient().connect()) {
		return -2;
	}
	if (!getClient().ping()) {
		return -3;
	}

	return 0;
}

} /* namespace Riak */
