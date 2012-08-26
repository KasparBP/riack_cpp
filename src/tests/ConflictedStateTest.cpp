

#include "ConflictedStateTest.h"
#include "../Object.h"
#include "../RiakExceptions.h"
#include <string.h>

namespace Riak {

std::string ConflictedStateTest::name = "conflicted";

ConflictedStateTest::ConflictedStateTest(const std::vector<std::string> &arguments)
	: RiakTestCase(arguments) {
}

ConflictedStateTest::~ConflictedStateTest() {
}

void ConflictedStateTest::setup() {
	testKeyName = "ConflictedStateTestKey1";
	getClient().connect();
	bucket = std::auto_ptr<Bucket>(new Bucket(&getClient(), getTestBucketName()));
}

void ConflictedStateTest::tearDown() {
	bucket.reset();
}

int ConflictedStateTest::runTest() {
	char value1[] = "value1";
	char value2[] = "value2";
	Object object(bucket.get(), testKeyName);
	object.setValue((uint8_t*)value1, strlen(value1));
	try {
		object.store();
	} catch (...) {
		return 1;
	}
	Object object2(bucket.get(), testKeyName);
	object2.setValue((uint8_t*)value2, strlen(value2));
	try {
		object2.store();
	} catch (ConflictedException& exception) {
		object.fetch();
		return 0;
	} catch (...) {
		return 3;
	}
	return 4;
}

}

