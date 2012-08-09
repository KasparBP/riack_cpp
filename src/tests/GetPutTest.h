
#ifndef GETPUTTEST_H_
#define GETPUTTEST_H_

#include <memory>
#include "RiakTestCase.h"
#include "../Bucket.h"

namespace Riak {

class GetPutTest : public RiakTestCase {
public:
	GetPutTest(const std::vector<std::string> &arguments);
	virtual ~GetPutTest();

	virtual void setup();
	virtual void tearDown();
	virtual int runTest();

	static std::string name;
private:
	std::auto_ptr<Bucket> bucket;
};

} /* namespace Riak */
#endif /* GETPUTTEST_H_ */
