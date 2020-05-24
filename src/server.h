#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdlib.h>
#include <getopt.h>
#include <dlfcn.h>

#include "player_def.h"


int compute_next_player();

enum shape { SQUARE = 0, TRIANGLE = 1, HEXAGONAL = 2, ERROR_SHAPE = -1 };

#endif
