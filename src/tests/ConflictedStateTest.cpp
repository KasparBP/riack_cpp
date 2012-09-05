

#include "ConflictedStateTest.h"
#include "../Object.h"
#include "../RiakExceptions.h"
#include "../DefaultResolver.h"
#include <string.h>
#include <iostream>

#if defined (_WIN32) 
#include <windows.h>
#endif

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
	bucket = std::auto_ptr<Bucket>(new Bucket(getClient(), getTestBucketName()));
	bucket->setAllowMult(true);
	bucket->setNVal(3);
	getClient().applyBucketProperties(*bucket);
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
	} catch (ConflictedException&) {
		// Leftover conflict most likely, delete and wait for it to propegate
		getClient().del(*bucket, object);
#if defined (_WIN32) 
		Sleep(5000);
#else
		sleep(5);
#endif
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
	getClient().store(*bucket, testKeyName, object);
	try {
 		getClient().fetch(*bucket, object);
	} catch (ConflictedException& exception) {
		try {
			DefaultResolver resolver;
			Object resolved = getClient().resolve(resolver, exception);
			getClient().store(*bucket, testKeyName, resolved);
			return 0;
		} catch (std::runtime_error& err) {
			std::cout << err.what() << std::endl;
			return 2;
		}
	} catch (...) {
		return 3;
	}
	return 4;
}

}

