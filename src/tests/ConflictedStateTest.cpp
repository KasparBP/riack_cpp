

#include "ConflictedStateTest.h"

namespace Riak {

std::string ConflictedStateTest::name = "conflicted";

ConflictedStateTest::ConflictedStateTest(const std::vector<std::string> &arguments)
	: RiakTestCase(arguments) {

}

ConflictedStateTest::~ConflictedStateTest() {
}

void ConflictedStateTest::setup() {
	getClient().connect();
}

void ConflictedStateTest::tearDown() {

}

int ConflictedStateTest::runTest() {
	return 0;
}

}

