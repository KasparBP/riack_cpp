
#include "RiakTestCase.h"

namespace Riak {

RiakTestCase::RiakTestCase(const std::vector<std::string> &arguments) : TestCase(arguments) {
	RiakCpp::init();
}

RiakTestCase::~RiakTestCase() {
	RiakCpp::cleanup();
}

} /* namespace Riak */
