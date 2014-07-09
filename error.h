#ifndef __DISSASSEBLE_PPC64_ERROR_H__
#define __DISSASSEBLE_PPC64_ERROR_H__
#include <inttypes.h>
#include <capstone/capstone.h>

const char* get_err(csh *handle);

#endif
