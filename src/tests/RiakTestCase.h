
#ifndef RIAKTESTCASE_H_
#define RIAKTESTCASE_H_

#include "TestCase.h"
#include "../RiackCpp.h"
#include "../Client.h"

namespace Riak {

class RiakTestCase : public TestCase {
public:
	RiakTestCase(const std::vector<std::string> &arguments);
	virtual ~RiakTestCase();
protected:
private:
};

} /* namespace Riak */
#endif /* RIAKTESTCASE_H_ */
