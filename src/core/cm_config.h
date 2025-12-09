#ifndef CM_CONFIG_H
#define CM_CONFIG_H

#ifdef USE_DOUBLE
typedef double cm_real_t;
#else
typedef float cm_real_t;
#endif

#ifdef CM_DEBUG
#include <assert.h>
#define CM_ASSERT(x) assert(x)
#else
#define CM_ASSERT(x) ((void)0) 
#endif

//TODO: platform compile config

#endif
