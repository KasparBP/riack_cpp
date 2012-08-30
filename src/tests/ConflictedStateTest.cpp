

#include "ConflictedStateTest.h"
#include "../Object.h"
#include "../RiakExceptions.h"
#include <string.h>
#include <iostream>

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
	Object object(testKeyName);
	getClient().fetch(*bucket, object);
	object.setValue((uint8_t*)value1, strlen(value1));
	sleep(1000);
	try {
		getClient().store(*bucket, testKeyName, object);
	} catch (...) {
		return 1;
	}
//	Object object2(bucket.get(), testKeyName);
	object.setValue((uint8_t*)value2, strlen(value2));
	try {
		getClient().store(*bucket, testKeyName, object);
//		object2.store();
	} catch (ConflictedException& exception) {
		try {
			// object.fetch();
			// object.chooseSibling(0);
			// object.store();
			std::cout << "plappe" << std::endl;
		} catch (...) {
			return 4;
		}
		return 0;
	} catch (...) {
		return 3;
	}
	return 4;
}

}

