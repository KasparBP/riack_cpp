/*
 * ConnectionTest.cpp
 *
 *  Created on: Aug 8, 2012
 *      Author: kpn
 */

#include "ConnectionTest.h"

namespace Riak {

std::string ConnectionTest::name = "connection";

ConnectionTest::ConnectionTest(const std::vector<std::string> &arguments) : RiakTestCase(arguments) {

}

ConnectionTest::~ConnectionTest() {

}

int ConnectionTest::runTest()
{
	return 0;
}

} /* namespace Riak */
