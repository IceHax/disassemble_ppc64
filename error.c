#include "error.h"

const char* get_err(csh *handle){
	return cs_strerror(cs_errno(*handle));
}

