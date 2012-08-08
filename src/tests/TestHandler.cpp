/*
 * TestHandler.cpp
 *
 *  Created on: Aug 7, 2012
 *      Author: kpn
 */

#include "TestHandler.h"
#include <iostream>

int main(int argc, char* argv[])
{
	std::vector<std::string> arguments;
	if (argc < 4) {
		std::cout << "Missing arguments" << std::endl;
		return -1;
	}
	TestHandler handler;
	for (int i=2; i<argc; ++i) {
		arguments.push_back(argv[i]);
	}

	return handler.runTest(arguments);
}


TestHandler::TestHandler() {
}

TestHandler::~TestHandler() {
}

int TestHandler::runTest(const std::vector<std::string> arguments)
{
	return 0;
}
