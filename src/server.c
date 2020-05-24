#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"player_operation.h"
#include "server.h"
#include "graph_operation.h"
#include <math.h>
#include <assert.h>

#define MAX_VERTICES 1000
void *libfstest_handle;

static int size = 10;
static char* shape = "c";
static int graph_shape = -1;

void parse_opts(int argc, char* argv[])
{
  int opt;
  while ((opt = getopt(argc, argv, "m:t:")) != -1)
    {
      switch (opt)
	{
	case 'm':
	  size = atoi(optarg);
	  break;
	case 't':
	  shape = optarg;
	  break;
	default: 
	  printf("Erreur : paramètres acceptés parmi -m et -t");
	  exit(EXIT_FAILURE);
	}
    }
}


static int previous_player = 0;
//Calcule qui joue le suivant.

int compute_next_player()
{
  if (previous_player == 1)
    {
      previous_player = 0;
    }
  else
    {
      previous_player = 1;
    }
  return previous_player;
}


//renvoie le nombre de case libre dans "graph".
int nb_free(struct graph_t* graph)
{
  int c = 0;
  for(int i = 0; i < (int)graph->num_vertices; i++)
    {
      if ((gsl_spmatrix_get(graph->o, BLACK, i) == 0) && gsl_spmatrix_get(graph->o, WHITE, i) == 0)
	c++;
    }
  return c;
}


//renvoie un entier strictement positif si le coup "play" est possible. 0 sinon. 
int avaible_to_play(struct move_t play, struct graph_t* graph, enum color_t player_id)
{
   int num_vertices = graph->num_vertices;
   return ( (int) play.m >= 0) && (play.m < ((size_t) num_vertices) ) && ( gsl_spmatrix_get(graph->o,BLACK,play.m) != 1 ) && ( gsl_spmatrix_get(graph->o,WHITE, play.m) != 1 ) && ( play.c == player_id );
}

int print_problem(struct move_t play, struct graph_t* graph, enum color_t player_id)
{
  int i = avaible_to_play(play, graph, player_id);
  if (!(i))
    printf("Erreur : coup invalide du joueur : %d\n", player_id);
  return i;
}



int main(int argc, char* argv[])
{
  //int size = 4;
  //int graph_shape = 0;
  printf("argc = %d\n",argc);
  //for options...
  parse_opts(argc, argv);
  printf("argc = %d\n",argc);

  //Pour la detection des erreurs en parametres.
  if ( strcmp(shape, "c") == 0 )
    graph_shape = 0;
  else if (strcmp(shape, "h") == 0)
    graph_shape = 1;
  else
    {
      printf("Erreur : Veuillez rentrer  une forme de graphe reconnue parmi c,t,h \n");
      exit (EXIT_FAILURE);
    }
  if ( ! ( 0 < size && size < MAX_VERTICES ) )
    {
      printf("Erreur : La taille rentrée n'est pas valide\n");
      exit (EXIT_FAILURE);
    }
  
    if (argc < 3 )
    {
      printf("Erreur : Veuillez entrez moins deux librairies dynamiques\n");
      exit (EXIT_FAILURE);
    }
  //compares the two librairies
  if ( !strcmp(argv[argc-2], argv[argc-1]) )
    {
      printf("Erreur : même bibliothèques dynamiques\n");
      exit (EXIT_FAILURE);
    }


  struct graph_t* graph = malloc(sizeof(struct graph_t));
  graph_construction(size, graph_shape, graph);
  //struct graph_t* graph_copy = malloc(sizeof(struct graph_t));

  struct graph_t* graph_copy1;
  
  graph_copy1 = graph_copy_function(graph, size);
  struct graph_t* graph_copy2;
  graph_copy2 = graph_copy_function(graph, size);
  
  size_t sources[2];
  init_sources(sources,graph_shape,size+1);
  size_t dst0[size];
  size_t dst1[size];
  size_t* destinations[2] = {dst0,dst1};
  init_destinations(destinations,graph_shape,size+1);
  
  printf("nb_free : %d\n", nb_free(graph));
  
  //player0 initialization
  struct player* player0 = malloc(sizeof(struct player));
  player0->player_path = argv[argc - 2];

  void* player0_lib = dlopen(player0->player_path, RTLD_LAZY);
  //verifys if the first librairy is a library
  if (!(libfstest_handle = player0_lib))
    {
      printf ("Erreur dlopen: %s\n", dlerror ());
 
      graph_free(graph_copy1);
      graph_free(graph_copy2);
      player_free(player0);
      graph_free(graph);
      exit (EXIT_FAILURE);
    }
  
  int p0 = initialize_player(player0, player0_lib);
  if ( !p0 )
    {
      printf ("Erreur dlsym: %s\n", dlerror ());
      graph_free(graph_copy1);
      graph_free(graph_copy2);
      player_free(player0);
      graph_free(graph);
      exit (EXIT_FAILURE);
    }
  
  player0->functions.initialize_graph(graph_copy1);
 

  
  //player1 initialization
  struct player* player1 = malloc(sizeof(struct player));
  player1->player_path = argv[argc - 1]; 

  void* player1_lib = dlopen(player1->player_path, RTLD_LAZY);
  //verifys if the second librairy is a library
  if (!(libfstest_handle = player1_lib))
    {
      printf ("Erreur dlopen: %s\n", dlerror ());
            
      graph_free(graph_copy2);

      player0->functions.finalize();
      
      dlclose(player0_lib);
      
      player_free(player0);
      player_free(player1);
      
      
      graph_free(graph);
      exit (EXIT_FAILURE);
    }
  
  int p1 = initialize_player(player1, player1_lib);
  if ( !p1 )
    {
      printf ("Erreur dlsym: %s\n", dlerror ());
      graph_free(graph_copy1);
      graph_free(graph_copy2);
      player_free(player0);
      graph_free(graph);
      exit (EXIT_FAILURE);
    }
  player1->functions.initialize_graph(graph_copy2);

  struct move_t first_move = player0->functions.propose_opening();
  
  

  
  if (player1->functions.accept_opening(first_move))
    {
      printf(" player0 : %zu\n", first_move.m);
      printf("-----accepte - proposition-----------------------\n");
    
      player1->functions.initialize_color(WHITE);
    
      player0->functions.initialize_color(BLACK);
    
      assert(print_problem(first_move, graph, BLACK));
      graph_update(graph, first_move);
      printf("%s est le joueur %d\n", player0->functions.get_player_name(), BLACK);
      printf("%s est le joueur %d\n", player1->functions.get_player_name(), WHITE);
    }
  else
    {
      printf("-----refuse - proposition-----------------------\n");
    
      player1->functions.initialize_color(BLACK);
    
      player0->functions.initialize_color(WHITE);
    
      printf("%s est le joueur %d\n",player0->functions.get_player_name() ,WHITE);
      printf("%s est le joueur %d\n", player1->functions.get_player_name(), BLACK);
    }

  
 

  int next_player;
 
  
  while(nb_free(graph) > 0) 
    {
      
      next_player = compute_next_player();
 
      if (next_player == 1)
	{

	first_move = player1->functions.play(first_move);
	printf(" player1 : %zu\n", first_move.m);
	assert(print_problem(first_move, graph, WHITE));
	graph_update(graph, first_move); //add condition "if possible"
	}
      else
	{
	first_move = player0->functions.play(first_move);
	
	printf(" player0 : %zu\n", first_move.m);
	assert(print_problem(first_move, graph, BLACK));
	graph_update(graph, first_move);
	}


      //determine si un des deux joueur gagne à ce tour
      int winner = who_win(sources,graph,destinations,size);
      if (winner != -1)
	{
	  printf("le gagnant est le joueur %d\n",winner);
	  break;
	}
    }
  
  if ( nb_free(graph) == 0 )
    printf("La partie s'est terminée sur un match nul \n");

 
  player0->functions.finalize();
  player1->functions.finalize();
  
  dlclose(player0_lib);
  dlclose(player1_lib);
  
  player_free(player0);
  player_free(player1);
  
  graph_free(graph);

  return 0;
}
