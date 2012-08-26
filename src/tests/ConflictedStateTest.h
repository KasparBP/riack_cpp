
#ifndef CONFLICTEDSTATETEST_H_
#define CONFLICTEDSTATETEST_H_

#include "RiakTestCase.h"
#include "../Bucket.h"
#include <string>

namespace Riak {

class ConflictedStateTest : public RiakTestCase {
public:
	ConflictedStateTest(const std::vector<std::string> &arguments);
	virtual ~ConflictedStateTest();

	virtual void setup();
	virtual void tearDown();
	virtual int runTest();

	static std::string name;
private:
	std::auto_ptr<Bucket> bucket;
	std::string testKeyName;
};

}

#endif /* CONFLICTEDSTATETEST_H_ */
