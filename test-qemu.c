#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "xxhash.h"
#include "qemu-xxhash.h"

#include <stdio.h>

int main(int __attribute__((unused)) argc, char  __attribute__((unused)) **argv)
{
	union {
		struct {
			uint64_t ab;
			uint64_t cd;
			uint32_t e;
			uint32_t f;
			uint32_t g;
			uint32_t h;
		};
		char u[32];
	} foo = { 0 };
	unsigned int i;

	for (i = 0; i < 0xffffffff; i++) {
		uint32_t h, q;

		memset(&foo, i, sizeof(foo));
		h = XXH32(&foo, sizeof(foo), QEMU_XXHASH_SEED);
		q = qemu_xxhash8(foo.ab, foo.cd, foo.e, foo.f, foo.g, foo.h);

		if (q != h) {
			fprintf(stderr, "Error: xxhash(%u) = 0x%x, qemu-xxhash(%u) = 0x%x\n",
				i, h, i, q);
			exit(1);
		}
	}
	return 0;
}
