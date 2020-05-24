#ifndef PLAYER_RAND_H
#define PLAYER_RAND_H

#include <graph.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "server.h"

static enum color_t player_id = NO_COLOR;
static struct graph_t* player_graph = NULL;


size_t next_move();

#endif
