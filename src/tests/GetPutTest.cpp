
#include "GetPutTest.h"
#include <string.h>
#include "../Object.h"
#include "../RiakExceptions.h"

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
	Object object("test_key_1__");//getClient().fetch(*bucket, "test_key_1__");
	object.setContentType("application/json");
	object.setValue((uint8_t*)data, strlen(data));

	try {
		getClient().store(*bucket, object.getKey(), object);
	} catch (ConflictedException&) {
		return 1;
	} catch (...) {
		return 1;
	}

	if (getClient().fetch(*bucket, object)) {
		if (strlen(data) != object.getValueLength() ||
			memcmp(data, object.getValue(), strlen(data)) != 0) {
			return 2;
		}
	} else {
		return 3;
	}
	getClient().del(*bucket, object);
	return 0;
}

} /* namespace Riak */
