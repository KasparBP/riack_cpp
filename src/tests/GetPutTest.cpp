
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
	Object obj(bucket.get(), "test_key_1__");
	obj.setContentType("application/json");
	obj.setValue((uint8_t*)data, strlen(data));

	try {
		obj.store();
	} catch (ConflictedException&) {
		obj.burry();
		return 1;
	} catch (...) {
		return 1;
	}

	if (obj.fetch() == Object::fetchedOk) {
		if (strlen(data) != obj.getValueLength() ||
			memcmp(data, obj.getValue(), strlen(data)) != 0) {
			return 2;
		}
	} else {
		return 3;
	}
	obj.burry();
	return 0;
}

} /* namespace Riak */
