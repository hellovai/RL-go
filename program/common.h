// Copyright 2014 (hellvai)

#ifndef __COMMON_H__
#define __COMMON_H__
#include "common/glog.h"
#include "common/gflags.h"

#define PLAYER_ONE 1
#define PLAYER_TWO 2

// generate a random number from [0,m] or [-m,m]
float frand(float m = 1.0, bool sign = false);
#endif
