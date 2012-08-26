/*
   Copyright 2012 Trifork A/S
   Author: Kaspar Pedersen

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef CONTENT_H_
#define CONTENT_H_


#include "RiackCpp.h"
#include "String.h"

namespace Riak {

class Content {
	friend void swap(Content& first, Content& second) throw();
public:
	Content();
	Content(const struct RIACK_CONTENT& content);
	Content(const Content& content);
	virtual ~Content();

	Content& operator=(Content other);

	void setContentType(const String& contentType);
	void setContentEncoding(const String& contentEncoding);

	void setValue(uint8_t *value, size_t valueLength);

	void setFromRiackContent(const struct RIACK_CONTENT& content, bool hasData);

	const String& getContentType() const;
	const String& getContentEncoding() const;
	const String& getVtag() const;

	const uint8_t* getValue() const;
	const size_t getValueLength() const;

	uint8_t* getValue();
	size_t getValueLength();
private:
	void reset();

	String contentType;
	String contentEncoding;
	String vtag;

	size_t valueLength;
	uint8_t *value;
};

} /* namespace Riak */
#endif /* CONTENT_H_ */
