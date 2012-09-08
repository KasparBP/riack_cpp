/*
 * MetadataArray.cpp
 *
 *  Created on: Sep 8, 2012
 *      Author: kpn
 */

#include "MetadataArray.h"

namespace Riak {

MetadataArray::MetadataArray() : metadataArray(NULL) {
}

MetadataArray::~MetadataArray() {
	reset();
}

void MetadataArray::reset() {
	if (metadataArray != NULL) {
		delete [] metadataArray;
		metadataArray = NULL;
	}
}

void MetadataArray::clear() {
	reset();
	metadatas.clear();
}

struct RIACK_PAIR *MetadataArray::getAsRiackPairArray() const {
	return metadataArray;
}

void MetadataArray::updateInternalArray() {
	reset();
	if (metadatas.size() > 0) {
		metadataArray = new struct RIACK_PAIR[metadatas.size()];
		for (size_t i=0; i<metadatas.size(); ++i) {
			metadataArray[i] = metadatas[i].getAsRiackPair();
		}
	}
}

void MetadataArray::addMetadata(const Metadata& metadata) {
	metadatas.push_back(metadata);
	updateInternalArray();
}

bool MetadataArray::removeMetadata(const Metadata& metadata) {
	std::vector<Metadata>::iterator iter = metadatas.begin();
	while (iter != metadatas.end()) {
		if (*iter == metadata) {
			metadatas.erase(iter);
			updateInternalArray();
			return true;
		}
	}
	return false;
}

const std::vector<Metadata>& MetadataArray::getMetadatas() const {
	return metadatas;
}

size_t MetadataArray::count() const {
	return metadatas.size();
}

} /* namespace Riak */
