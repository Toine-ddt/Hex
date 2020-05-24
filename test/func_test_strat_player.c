#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "graph_operation.h"
#include "player_operation.h"

#ifdef RAND
#include "player_rand.h"
#elif DJI
#include "Djiplayer.h"
#else
#error "Unrecognize strat"
#endif


void test__play(struct player* p)
{
  struct move_t move = p->functions.propose_opening();
  struct move_t a = p->functions.play(move);
  assert( a.c == BLACK || a.c == WHITE );
}

void test__get_player_name(struct player* p)
{
  char* name = p->functions.get_player_name();
  assert( ! strcmp(name, "Player_rand"));
}

void test__propose_opening(struct player* p)
{
  struct move_t move = p->functions.propose_opening();
  assert( 0 <= move.m  );
  assert( move.c == BLACK );
}


void test__accept_opening(struct player* p)
{
  struct move_t move = p->functions.propose_opening();
  int a = p->functions.accept_opening(move);
  assert( a == 0 || a == 1 );
}

void test__initialize_color(struct player* p)
{
  p->functions.initialize_color(BLACK);
}

void test__finalize(struct player* p)
{
  p->functions.finalize();
}

int main(int argc, char* argv[])
{
  printf("début\n");

  struct graph_t* t = malloc(sizeof(struct graph_t));
  graph_construction(10,0,t);
  struct graph_t* graph_copy;
  graph_copy = graph_copy_function(t, 10);

  struct player* p = malloc(sizeof(struct player));

  printf("adresse de p: %p\n",p);

  void* player_lib;
  
  p->player_path = "install/libplayer1.so";

  player_lib = dlopen(p->player_path, RTLD_LAZY);
  
  printf("adresse de p: %p\n",p);
  initialize_player(p, player_lib);
  printf("adresse de p: %p\n",p);

  p->functions.initialize_graph(graph_copy);
  printf("adresse de p: %p\n",p);
   
  test__get_player_name(p);

  printf("p->functions.get_player_name : %s\n",p->functions.get_player_name());
  
  test__propose_opening(p);
  test__accept_opening(p);
  test__initialize_color(p);
  test__play(p);
  test__finalize(p);

  dlclose(player_lib);
  
  player_free(p);
  graph_free(t);
  return 0;
}
