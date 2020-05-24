#include "player_rand.h"
#include "player.h"
#include "server.h"
#include "graph_operation.h"
#include <assert.h>

struct move_t jok_Fmove_mem = { .m = INT_MAX };
int index_opening = 0;


int avaible_to_play(int play)
{
   int num_vertices = player_graph->num_vertices;
  return (play >= 0) && (play < num_vertices) && ( gsl_spmatrix_get(player_graph->o,BLACK,play) != 1 ) && ( gsl_spmatrix_get(player_graph->o,WHITE, play) != 1 );
}


void graph_updatee(struct graph_t* graph, struct move_t move)
{
  //printf("move.c : %d\n", move.c);
  //printf("move.m : %d\n\n", move.c);
  gsl_spmatrix_set(graph->o, move.c, move.m, 1);
}



// Determine the next avaible move
size_t next_move()
{
  int n = player_graph->num_vertices;
  int t[n];
  int size = 0;
  for (int i = 0; i < n ; i++)
    {
      if ( ( gsl_spmatrix_get(player_graph->o,BLACK,i) != 1 ) && ( gsl_spmatrix_get(player_graph->o,WHITE,i) != 1 ))
	{
	  t[size] = i;
	  size++;
	}
    }
  int ind;
  if (size != 0)
  ind = rand()%size;
  else{
    ind = 0;
  }
  //printf("rand : %d\n", ind);
  //printf("size : %d\n", size);
  size_t next  = (size_t)t[ind];
  
  return next;
}



/* Access to player informations
 * RETURNS:
 * - the player name as an [a-zA-Z0-9 -_]* string
 */
char const* get_player_name()
{
  return "Player_rand";
}

/* Returns a sequence of three moves for an opening
 * PRECOND:
 * - a call to initialize_graph has been made
 * RETURNS:
 * - a correct move inside the graph
 */
struct move_t propose_opening()
{
  index_opening =1;
  //printf("pointeur de p : %p\n",player_graph);
  //printf("player_graph.nbvertices = %zu",player_graph->num_vertices);
  int bk = next_move();
  size_t first = (size_t)bk;
  jok_Fmove_mem.m = bk;
  jok_Fmove_mem.c = BLACK;
  struct move_t first_move = { .m = first };
  first_move.c = BLACK;
  return first_move;
}

/* Acceptation of the opening
 * PARAM:
 * - opening : a move inside the graph
 * PRECOND:
 * - a call to initialize_graph has been made
 * - the move is valid with regard to this graph
 * RETURNS:
 * - a boolean telling if the player accepts the opening
 */
int accept_opening(const struct move_t opening)
{
  //printf( "la couleur : %d", opening.c);
  graph_updatee(player_graph, opening);
  //int n = rand()%2;
  return 1;
}

/* Player graph initialization
 * PARAM:
 * - graph : the graph where the game is played
 * PRECOND:
 * - `graph` is a heap-allocated copy of the graph where the game is
 *   played, that must be freed in the end
 * - initialize_graph has never been called before
 */

void initialize_graph(struct graph_t* graph)
{
  //printf("pointeur de player_graph : %p\n",player_graph);
  //player_graph = malloc(sizeof(struct graph_t));
  //graph_copy_function(player_graph, graph);
  assert(graph != NULL);
  player_graph = graph;
  srand(time(NULL));
}


/* Player color initialization
 * PARAM:
 * - id : the color assigned to the player
 * PRECOND:
 * - id is either BLACK or WHITE
 * - initialize_color has never been called before
 */
void initialize_color(enum color_t id)
{
  if( player_id == NO_COLOR )
    player_id = id;
}

int he_accept()
{
  return ((player_id == BLACK) && (index_opening == 1));
}

/* Computes next move
 * PARAM:
 * - previous_move: the move from the previous player
 * RETURNS:
 * - the next move for the player.
 */
struct move_t play(struct move_t previous_move)
{
  if (he_accept())
    graph_updatee(player_graph, jok_Fmove_mem);
  graph_updatee(player_graph, previous_move);
  size_t next = next_move();
  struct move_t next_move = { .m = next };
  next_move.c = player_id;
  //printf("next  : %zu", next);
  graph_updatee(player_graph, next_move); 
  return next_move;
}

/* Announces the end of the game to the player, and cleans up the
   memory he may have been using.
 * POSTCOND:
 * - every allocation done during the calls to initialize and play
 *   functions must have been freed
 */

void finalize()
{
  gsl_spmatrix_free(player_graph->t);
  gsl_spmatrix_free(player_graph->o);
  free(player_graph);
}
