#ifndef _PLAYER_OPERATION_
#define _PLAYER_OPERATION_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player_def.h"


int initialize_player(struct player*, void* player_lib);
void player_free(struct player* );

#endif
