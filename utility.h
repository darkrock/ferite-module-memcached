
#include <ferite.h>

typedef struct __ferite_memcached {
	FeriteScript *script;
	FeriteObject *block;
} FeriteMemcached;

static memcached_return_t ferite_memcached_key_process( memcached_st *ptr, const char *key, size_t key_length, void *context );
