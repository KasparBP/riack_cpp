
#include "GetPutTest.h"
#include <string.h>
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
	char data[] = "test data";
	Object obj(bucket.get(), "test_key_1__");
	obj.getContent(0)->setContentType("application/json");
	obj.getContent(0)->setValue((uint8_t*)data, strlen(data));

	if (!obj.store()) {
		return 1;
	}

	if (obj.fetch()) {
		if (strlen(data) != obj.getContent(0)->getValueLength() ||
			memcmp(data, obj.getContent(0)->getValue(), strlen(data)) != 0) {
			return 2;
		}
	} else {
		return 3;
	}
	return 0;
}

} /* namespace Riak */
