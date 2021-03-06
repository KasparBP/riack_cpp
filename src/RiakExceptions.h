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
#ifndef RIACKEXCEPTION_H_
#define RIACKEXCEPTION_H_

#include <stdexcept>
#include <string>
#include <vector>
#include "String.h"
#include "Resolver.h"

namespace Riak {

class Client;
class ThrowRiackException {
public:
	static void throwRiackException(Client& client, int riackStatus);
};

class TransientException : public std::runtime_error {
public:
	explicit TransientException(const std::string& message)
		: std::runtime_error(message) {}
	virtual ~TransientException() throw() {}
};

class ConflictedException : public std::runtime_error {
public:
	explicit ConflictedException(const String& bucket, const String& key,
			ConflictedObjectsVector& conflictedObjects)
		: std::runtime_error("conflicted"), bucket(bucket), key(key), conflictedObjects(conflictedObjects) {}
	virtual ~ConflictedException() throw() {}

	const String& getBucketName() const {return bucket;}
	const String& getKeyName() const {return key;}
	const ConflictedObjectsVector getConflictedObjects() const {return conflictedObjects;}
private:
	const String bucket;
	const String key;
	const ConflictedObjectsVector conflictedObjects;
};

class ArgumentsError : public std::logic_error {
public:
	explicit ArgumentsError(const std::string& arg)
		: std::logic_error(arg) {}
	virtual ~ArgumentsError() throw() {}
};

class ResponseError : public std::runtime_error {
public:
	explicit ResponseError(const std::string& message, uint32_t error_code)
		: std::runtime_error(message), error_code(error_code) {}
	virtual ~ResponseError() throw() {}

	const uint8_t getErrorCode() const {return error_code;}
private:
	const uint32_t error_code;
};

class ConnectionException : public std::runtime_error {
public:
	explicit ConnectionException(const std::string& message)
			: std::runtime_error(message) {}
	virtual ~ConnectionException() throw() {}
};

}

#endif /* RIACKEXCEPTION_H_ */
