#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "uct.h"

//UCT
UCT::UCT() {
	root = NULL;
	size = 0;
}