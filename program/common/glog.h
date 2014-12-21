#ifndef __GLOG_H__
#define __GLOG_H__

#ifdef USE_GLOG
#define GLOG(x) x
#include <glog/logging.h>
#else
#define GLOG(x)
#endif

#endif
