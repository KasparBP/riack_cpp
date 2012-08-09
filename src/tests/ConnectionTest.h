
#ifndef CONNECTIONTEST_H_
#define CONNECTIONTEST_H_

#include "RiakTestCase.h"

namespace Riak {

class ConnectionTest : public RiakTestCase {
public:
	ConnectionTest(const std::vector<std::string> &arguments);
	virtual ~ConnectionTest();

	virtual void setup() {}
	virtual void tearDown() {}
	virtual int runTest();

	static std::string name;
};

} /* namespace Riak */
#endif /* CONNECTIONTEST_H_ */
