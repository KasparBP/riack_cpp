/*
 * ConnectionTest.cpp
 *
 *  Created on: Aug 8, 2012
 *      Author: kpn
 */

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

	return 0;
}

} /* namespace Riak */
