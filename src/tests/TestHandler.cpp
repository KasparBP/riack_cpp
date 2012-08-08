
#include "TestHandler.h"
#include "ConnectionTest.h"
#include <iostream>

using namespace Riak;

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

TestCase* TestHandler::testFactory(const std::string &name, const std::vector<std::string> &arguments)
{
	if (name.compare(ConnectionTest::name) == 0) {
		return new ConnectionTest(arguments);
	}
	return 0;
}

int TestHandler::runTest(const std::vector<std::string> &arguments)
{
	int result = -1;
	TestCase* testCase = testFactory(arguments[0], arguments);
	if (testCase) {
		result = testCase->runTest();
		delete testCase;
	}
	return result;
}
