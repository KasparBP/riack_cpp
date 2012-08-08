/*
 * TestHandler.h
 *
 *  Created on: Aug 7, 2012
 *      Author: kpn
 */

#ifndef TESTHANDLER_H_
#define TESTHANDLER_H_

#include <vector>
#include <string>

class TestHandler {
public:
	TestHandler();
	virtual ~TestHandler();

	int runTest(const std::vector<std::string> arguments);
};

#endif /* TESTHANDLER_H_ */
