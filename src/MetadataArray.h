/*
 * MetadataArray.h
 *
 *  Created on: Sep 8, 2012
 *      Author: kpn
 */

#ifndef METADATAARRAY_H_
#define METADATAARRAY_H_

#include "Metadata.h"
#include "RiackCppDefines.h"
#include <vector>

namespace Riak {

class MetadataArray {
public:
	MetadataArray();
	virtual ~MetadataArray();

	void clear();

	void addMetadata(const Metadata& metadata);
	bool removeMetadata(const Metadata& metadata);
	const std::vector<Metadata>& getMetadatas() const;
	size_t count() const;

	struct RIACK_PAIR *getAsRiackPairArray() const;
private:
	void updateInternalArray();
	void reset();

	std::vector<Metadata> metadatas;
	struct RIACK_PAIR *metadataArray;
};

} /* namespace Riak */
#endif /* METADATAARRAY_H_ */
