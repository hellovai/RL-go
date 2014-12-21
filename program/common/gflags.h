#ifndef __GFLAGS_H__
#define __GFLAGS_H__

#ifdef USE_GFLAGS
#include <gflags/gflags.h>
#define GFLAGS(x, y) x
#else
#define GFLAGS(x, y) y
#endif

#endif
