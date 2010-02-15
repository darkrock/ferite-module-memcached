
#include <libmemcached/memcached.h>
#include "utility.h"

static memcached_return_t ferite_memcached_key_process( memcached_st *ptr, const char *key, size_t key_length, void *_context ) {
	FeriteMemcached *context = (FeriteMemcached*)_context;
	FeriteScript *script = context->script;
	FeriteObject *block = context->block;
	FeriteVariable *key_variable = ferite_create_string_variable_from_ptr( script, "", (char*)key, key_length, FE_CHARSET_DEFAULT, FE_STATIC );
	FeriteVariable *params[2];
	FeriteFunction *function = NULL;
	
	params[0] = key_variable;
	params[1] = NULL;
	
	function = ferite_object_get_function_for_params( script, block, "invoke", params );
	if( function ) {
		FeriteVariable *return_variable = ferite_call_function( script, block, NULL, function, params );
		if( return_variable ) {
			ferite_variable_destroy( script, return_variable );
		}
	}
	
	ferite_variable_destroy( script, key_variable );
	return MEMCACHED_SUCCESS;
}