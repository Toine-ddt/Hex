#ifndef PLAYER_DEF_
#define PLAYER_DEF_

#include "move.h"
#include "graph.h"
#include "player.h"

struct functions{
  char const* (*get_player_name)(void);
  struct move_t (*propose_opening)(void);
  int (*accept_opening)(const struct move_t);
  void (*initialize_graph)(struct graph_t* graph);
  void(*initialize_color)(enum color_t);
  struct move_t (*play)(struct move_t);
  void (*finalize)(void);
};

struct player{
  char * player_path;
  char* name;
  //enum color_t id; the color is defined within the game not an id
  struct graph_t * player_graph;
  struct functions functions;
};


// initialize the player with the three functions.
/*void initialize_player(struct player*);*/

#endif
