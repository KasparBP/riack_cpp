
#include "GetPutTest.h"

namespace Riak {

std::string GetPutTest::name = "getput";

GetPutTest::GetPutTest(const std::vector<std::string> &arguments)
	: RiakTestCase(arguments)
{

}

GetPutTest::~GetPutTest()
{
}

void GetPutTest::setup()
{
	getClient().connect();
	bucket = std::auto_ptr<Bucket>(new Bucket(&getClient(), getTestBucketName()));
}

void GetPutTest::tearDown()
{
	bucket.reset(0);
}

int GetPutTest::runTest()
{
	return 0;
}

} /* namespace Riak */
