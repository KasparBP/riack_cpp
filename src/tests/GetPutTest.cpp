
#include "GetPutTest.h"
#include "../Object.h"

namespace Riak {

std::string GetPutTest::name = "getput";

GetPutTest::GetPutTest(const std::vector<std::string> &arguments)
	: RiakTestCase(arguments) {

}

GetPutTest::~GetPutTest() {
}

void GetPutTest::setup() {
	getClient().connect();
	bucket = std::auto_ptr<Bucket>(new Bucket(&getClient(), getTestBucketName()));
}

void GetPutTest::tearDown() {
	bucket.reset(0);
}

int GetPutTest::runTest() {
	Object obj(bucket.get(), "test_key_1__");
	obj.getContent(0)->setContentType("application/json");
	if (obj.store()) {
		return 0;
	}
	return 1;
}

} /* namespace Riak */
