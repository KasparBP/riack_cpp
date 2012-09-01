

#include "ConflictedStateTest.h"
#include "../Object.h"
#include "../RiakExceptions.h"
#include "../DefaultResolver.h"
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
	Object object(testKeyName);
	getClient().del(*bucket, object);
	bucket.reset();
}

int ConflictedStateTest::runTest() {
	char value1[] = "value1";
	char value2[] = "value2";
	Object object(testKeyName);
	try {
		getClient().fetch(*bucket, object);
	} catch (ConflictedException& exception) {
		// Leftover conflict most likely, delete and wait for it to propegate
		getClient().del(*bucket, object);
		sleep(5);
		getClient().fetch(*bucket, object);
	} catch (std::runtime_error& other) {
		std::cout << other.what() << std::endl;
	}
	object.setValue((uint8_t*)value1, strlen(value1));
	try {
		getClient().store(*bucket, testKeyName, object);
	} catch (...) {
		return 1;
	}
	object.setValue((uint8_t*)value2, strlen(value2));
	try {
		getClient().store(*bucket, testKeyName, object);
	} catch (ConflictedException& exception) {
		try {
			DefaultResolver resolver;
			Object resolved = getClient().resolve(resolver, exception);
			getClient().store(*bucket, testKeyName, resolved);
			// Fetch to make sure we are not conflicted
			return 0;
		} catch (...) {
			return 2;
		}
	} catch (...) {
		return 3;
	}
	return 4;
}

}

