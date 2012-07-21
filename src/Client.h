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
#ifndef RIACKCPP_CLIENT_H__
#define RIACKCPP_CLIENT_H__

#include <string>
#include "RiackCpp.h"

namespace Riak {

class Client {
public:
	Client(const std::string& host, int port);
	virtual ~Client();

private:
	bool connect();

	std::string host;
	int port;
	bool connected;

	struct RIACK_CLIENT *client;
};

} /* namespace Riak */

#endif /* RIACKCPP_CLIENT_H__ */
