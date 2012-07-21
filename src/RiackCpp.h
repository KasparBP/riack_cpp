
#ifndef RIACK_CPP__H__
#define RIACK_CPP__H__

extern "C" {
#include <riack.h>
}

class Riak {
public:
	static void init() {
		riack_init();
	}
	static void cleanup() {
		riack_cleanup();
	}
};

#endif //RIACK_CPP__H__
