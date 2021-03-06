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

#include "RiakExceptions.h"
#include "Client.h"

namespace Riak {

void ThrowRiackException::throwRiackException(Client& client, int riackStatus) {
	if (riackStatus == RIACK_ERROR_COMMUNICATION) {
		throw TransientException("Communication error");
	} else if (riackStatus == RIACK_ERROR_RESPONSE) {
		throw ResponseError(client.getRiackClient()->last_error, 
			client.getRiackClient()->last_error_code);
	} else if (riackStatus == RIACK_ERROR_INVALID_INPUT) {
		throw ArgumentsError("Invalid arguments passed to underlying Riack library");
	}
}

}