
#ifndef TESTHANDLER_H_
#define TESTHANDLER_H_

#include "TestCase.h"
#include <vector>
#include <string>

class TestHandler {
public:
	TestHandler();
	virtual ~TestHandler();

	int runTest(const std::vector<std::string> &arguments);
protected:
	Riak::TestCase* testFactory(const std::string &name, const std::vector<std::string> &arguments);
};

#endif /* TESTHANDLER_H_ */
