
#ifndef CONFLICTEDSTATETEST_H_
#define CONFLICTEDSTATETEST_H_

#include "RiakTestCase.h"

namespace Riak {

class ConflictedStateTest : public RiakTestCase {
public:
	ConflictedStateTest(const std::vector<std::string> &arguments);
	virtual ~ConflictedStateTest();

	virtual void setup();
	virtual void tearDown();
	virtual int runTest();

	static std::string name;
};

}

#endif /* CONFLICTEDSTATETEST_H_ */
