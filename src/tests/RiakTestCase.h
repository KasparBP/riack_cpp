
#ifndef RIAKTESTCASE_H_
#define RIAKTESTCASE_H_

#include "TestCase.h"
#include "../RiackCpp.h"
#include "../String.h"
#include "../Client.h"
#include <memory>

namespace Riak {

class RiakTestCase : public TestCase {
public:
	RiakTestCase(const std::vector<std::string> &arguments);
	virtual ~RiakTestCase();

	const String getTestBucketName() const;
protected:

	Client& getClient();
private:
	std::auto_ptr<Client> client;
};

} /* namespace Riak */
#endif /* RIAKTESTCASE_H_ */
