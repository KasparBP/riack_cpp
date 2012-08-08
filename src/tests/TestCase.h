
#ifndef __TESTCASE_H___
#define __TESTCASE_H___

#include <vector>
#include <string>

namespace Riak {

class TestCase {
public:
	TestCase(const std::vector<std::string> &arguments) {this->arguments = arguments;}
	virtual ~TestCase() {}

	const std::vector<std::string> &getArguments() {return arguments;}

	virtual void setup() = 0;
	virtual void tearDown() = 0;
	virtual int runTest() = 0;
private:
	std::vector<std::string> arguments;
};

} /* namespace Riak */
#endif /* __TESTCASE_H___ */
