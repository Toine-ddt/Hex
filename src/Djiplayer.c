#include <limits.h>
#include <stdio.h>
#include"graph_operation.h"
#include "Djiplayer.h"
#include <assert.h>
#include <time.h>
#include "server.h"
#include "player.h"
#include <stdlib.h>


struct move_t jok_Fmove_mem = { .m = INT_MAX };

int current_Vertex_mem = INT_MAX; //the last move_variable
int last_ending_move = INT_MAX;
int index_opening = 0;

//met à jour le graph "graph" par "move"
void graph_updatee(struct graph_t* graph, struct move_t move)
{
  gsl_spmatrix_set(graph->o, move.c, move.m, 1);
}

//retourne 1 si c'est mon premier coup. 0 sinon
int ismy_first_move()
{
  return current_Vertex_mem == INT_MAX;
}

int* black_ends = NULL;
int* black_starts = NULL;
//cette fonction est appelée seulement dans le début
//pour determiner un point de début et de fin.
//sont but est de determiner les bords noirs.
int num_Bends = INT_MAX;
void black_SE_possibilities()
{
  assert(num_Bends == INT_MAX);
  
  int num_vertices = player_graph->num_vertices;
  black_starts = malloc(num_vertices*sizeof(int));
  black_ends = malloc(num_vertices*sizeof(int));

  //printf("@ black_starts : %p\n", black_starts);
  //printf("@ black_ends : %p\n", black_ends);
  
  
  int num_Bstarts = 0;
  num_Bends = 0;
  int i = 0;
  while (num_Bstarts < num_vertices && gsl_spmatrix_get(player_graph->o, BLACK, num_Bstarts) == 1)
    {
	
      black_starts[num_Bstarts] = num_Bstarts;
      num_Bstarts++; // num_Bstarts == m
    }
  i = num_Bstarts;
  while((gsl_spmatrix_get(player_graph->o, BLACK, i) == 0) && ( i < num_vertices))
    {
      i++;
    }
  
  while ((i < num_vertices) && gsl_spmatrix_get(player_graph->o, BLACK, i) == 1)
    {
	
      black_ends[num_Bends] = i;
      num_Bends++;
      i++;
    }
  }

//retourne un sommet d'arrivé noir.

int black_ending_move()
{
  assert(num_Bends != INT_MAX);
  return black_ends[num_Bends - 2];  
}

//retourne un point de depart noir.
int black_starting_move()
{
  assert(num_Bends != INT_MAX);
  return black_starts[num_Bends - 2]; 
}

int* whites = NULL;
int* white_starts = NULL;
int* white_ends = NULL;
int num_Wends = INT_MAX;

void white_SE_possibilities()
{
  assert(num_Wends == INT_MAX);
  int num_vertices = player_graph->num_vertices;
  whites = malloc(num_vertices*sizeof(int));
  white_starts = malloc(num_vertices*sizeof(int));
  white_ends = malloc(num_vertices*sizeof(int));
  int num_whites = 0;
  int num_Wstarts = 0;
  num_Wends = 0;
  for(int i = 0; i < num_vertices; i++)
    {
      
      if (gsl_spmatrix_get(player_graph->o, WHITE, i) == 1)
	{

	  whites[num_whites] = i;
	  num_whites++;
	}	
    }  
  for(int j = 0; j < num_whites; j = j + 2)
    {
      white_starts[num_Wstarts] = whites[j];
      num_Wstarts++;

    }
  for(int k = 1; k < num_whites; k = k + 2)
    {
      white_ends[num_Wends] = whites[k];
      num_Wends++;      
    }
  assert(num_Wends == num_Wstarts);
  
  //return num_Wends;
    
}

int white_ending_move()
{
  return white_ends[num_Wends - 2];
}
int white_starting_move()
{
  return white_starts[num_Wends - 2]; 
}

//initialise un tableau de voisins.
void voisin_initialisation(int* vrai_voisins)
{
  
  int num_vertices = player_graph->num_vertices;
  for(int i = 0; i < num_vertices; i++)
  {
    vrai_voisins[i] = 0;
  }
}

//retourne 0 dans le cas ou le coup choisi ne peut pas être jouée.
//un entier non nul sinon. 
int avaible_to_play(int play)
{
   int num_vertices = player_graph->num_vertices;
  return (play >= 0) && (play < num_vertices) && ( gsl_spmatrix_get(player_graph->o,BLACK,play) != 1 ) && ( gsl_spmatrix_get(player_graph->o,WHITE, play) != 1 );
}


//met à 1 tout les voisins valable de Vertex dans le tableau "voisins".
void voisins_valables(int Vertex, int* voisins)
{
  int num_vertices = (int)player_graph->num_vertices;  
  for(int i = 0; i < num_vertices; i++)
    {
      if ((gsl_spmatrix_get(player_graph->t, Vertex, i) == 1) && avaible_to_play(i))
	voisins[i] = 1;
    }

}


//met à 1 tout les voisins valable de Vertex dans le tableau "voisins" pour l'algorithme Djikstra.
void voisins_valables_djikstra(int Vertex, int* voisins)
{
  
  int num_vertices = (int)player_graph->num_vertices;  
  for(int i = 0; i < num_vertices; i++)
    {
      
      if (player_id == BLACK)
	{
	  if ((((int)gsl_spmatrix_get(player_graph->t, Vertex, i) == 1)) && (gsl_spmatrix_get(player_graph->o, WHITE, i) != 1))
	    {
	      voisins[i] = 1;
	    }
	  else{
	    voisins[i] = 0;
	  }
	}
      else
	{
	  if ((((int)gsl_spmatrix_get(player_graph->t, Vertex, i) == 1)) && (gsl_spmatrix_get(player_graph->o, BLACK, i) != 1))
	    {
	      voisins[i] = 1;
	    }
	  else{
	    voisins[i] = 0;
	  }
	}
    }
}



//initialise le tableau de distance "dist" pour Djikstra.
void distance_initialisation(int starting_Vertex, int* dist)
{
  int num_vertices = player_graph->num_vertices;
  
  for(int i = 0; i < num_vertices; i++)
  {
     dist[i] = INT_MAX - 1000;
    
  }
 
  dist[starting_Vertex] = 0;
 
}

//initialise le tableau is_visited
void is_visited_initialisation(int* is_visited)
{
  int num_vertices = player_graph->num_vertices;
  if (player_id == BLACK)
    {
      for (int i = 0; i < num_vertices; i++)
	{
	  if (gsl_spmatrix_get(player_graph->o, WHITE, i) != 1)
	    is_visited[i] = 0;
	  else{
	    is_visited[i] = 1;
	  }
	}
    }

  if (player_id == WHITE)
    {
      for (int i = 0; i < num_vertices; i++)
	{
	  if(gsl_spmatrix_get(player_graph->o, BLACK, i) != 1)
	    is_visited[i] = 0;
	  else{
	    is_visited[i] = 1;
	  }
	}
    }
}

int still_Vertex(int* is_visited)
{
  int num_vertices = player_graph->num_vertices;
  for(int i = 0; i < num_vertices; i++)
  {
    if (is_visited[i] == 0)
    return 1;
  }
  return 0;
}


// retourne un entier positif s'il n y a plus de voisins valide.
// 0 sinon.

int pas_voisins(int* voisins_valides)
{
  
  int num_vertices = player_graph->num_vertices;
  for(int i = 0; i < num_vertices; i++)
    {
      if (voisins_valides[i] == 1)
	return 0;
    }
  return 1;
}


//retourne le premier voisin valide du tableau voisins_valides.
int first_voisins(int* voisins_valides)
{
  int num_vertices = player_graph->num_vertices;
  for(int i = 0; i < num_vertices; i++)
    {
      if (voisins_valides[i] == 1)
	return i;
    }
  return -1;
}


// retourne l'indice du sommet non visité du plus petite distance. 
int min_Vertex_distance(int* dist, int* is_visited)
{
  int num_vertices = player_graph->num_vertices;
  int min = INT_MAX;
  int min_index = -1;
  for (int i = 0; i < num_vertices; i++)
  {
    if (is_visited[i] == 0)
    {
      if ((dist[i] < min))
	{

	  min = dist[i];
	  min_index = i;
	}
      }
  }  
  return min_index;
}


//calcule le tableau des distances "dist" et de prédecesseur "prev" en utilisant l'algorithme
//de Djikstra.
void djikstra(int starting_Vertex, int* dist, int* is_visited, int* voisins, int* prev)
{
  
  int num_vertices = player_graph->num_vertices;
  
  int s1 = 99;
  
  distance_initialisation(starting_Vertex, dist);
  is_visited_initialisation(is_visited);

  
    while(still_Vertex(is_visited))
    {
        s1 = min_Vertex_distance(dist, is_visited);
	
        is_visited[s1] = 1;
	voisins_valables_djikstra(s1, voisins);
	for (int s2 = 0; s2 < num_vertices; s2++)
	  {
	    if ( (voisins[s2] == 1))
	      {
	      
		if (dist[s2] > dist[s1] + 1)
		  {
		  dist[s2] = dist[s1] + 1;
		  prev[s2] = s1;

		  }
	      }
	}
    } 
}

//initialise le tableau path .
//(ne pas oublier de mettre le path_lenght à 0).
void path_initialisation(int* path)
{
  int num_vertices = player_graph->num_vertices;
  for(int i = 0; i < num_vertices; i++)
    {
      path[i] = INT_MAX;
    }
}

//initialise le tableau prev.
//(ne pas oublier de mettre le path_lenght à 0).
void prev_initialisation(int* prev)
{
  int num_vertices = player_graph->num_vertices;
  for(int i = 0; i < num_vertices; i++)
    {
      prev[i] = -1;
    }
}

//construit le chemin de "starting_Vertex" vers "end_Vertex".
// (la case qui doit être jouée c'est la path[path_length - 2])
int path_construct(int* path,int* prev,int* dist, int* is_visited,int* voisins, int starting_Vertex, int end_Vertex) 
{
  int path_length = 0;
  int working_vertex = end_Vertex;	
  path_initialisation(path);
  prev_initialisation(prev);  
  djikstra(starting_Vertex, dist, is_visited, voisins, prev);
  while(working_vertex != starting_Vertex)
    {
      path[path_length] = working_vertex;
      path_length++;
       working_vertex = prev[working_vertex];
            
    }
  return path_length;
}


//renvoie un coup à jouer au hasard.
size_t next_move_rand()
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
  size_t next  = (size_t)t[ind];
  
  return next;
}
//my previous play == current vertex 


//renvoie le coup à jouer en utilisant l'algorithme de Djikstra.
size_t next_move()
{
  int num_vertices = player_graph->num_vertices;
  
  int voisins[num_vertices];
  int current_game_vertex = INT_MAX;
  current_game_vertex = current_Vertex_mem;
    
  if (ismy_first_move()) //forcement je suis blanc 
    {

      if (num_Wends == INT_MAX)
	white_SE_possibilities();
      
      if (num_Bends == INT_MAX)
	{
	black_SE_possibilities();
	}
      int opening_Vertex = white_starting_move();

      //je choisie un coup valable pour commencer
      int opening_voisins[num_vertices];
      voisin_initialisation(opening_voisins);
      voisins_valables(opening_Vertex, opening_voisins);
      int real_opening_voisin = first_voisins(opening_voisins);
      

      int closing_Vertex = white_ending_move();
      int closing_voisins[num_vertices];
      voisin_initialisation(closing_voisins);
      voisins_valables(closing_Vertex, closing_voisins);
      last_ending_move = first_voisins(closing_voisins);
      return real_opening_voisin;
    }

  //le cas ou je propose et l'autre accepte. je definie un END
  if (last_ending_move == INT_MAX)
    {
      int real_end_Vertex = black_ending_move();
      //printf("real_end_Vertex : %d\n", real_end_Vertex);
      int end_real_voisins[num_vertices];
      voisin_initialisation(end_real_voisins);
      voisins_valables(real_end_Vertex, end_real_voisins);  
      last_ending_move = first_voisins(end_real_voisins);    }
  
  int verification_voisins[num_vertices];
  voisin_initialisation(verification_voisins);
  voisins_valables(current_game_vertex, verification_voisins);

  if (pas_voisins(verification_voisins))
    {
      //printf("-------joue au hasard 0(pas de voisins)----\n");
      return next_move_rand();
    } 
  int dist[num_vertices];   
  int prev[num_vertices];
  int is_visited[num_vertices];
  int path[num_vertices];
  int path_length = 0;
  
  path_length = path_construct(path, prev, dist, is_visited, voisins, current_game_vertex, last_ending_move);

  size_t next  = (size_t)path[path_length - 1];   
  return next;
}

char const* get_player_name()
{
  return "DJI_PLAYER";
}


struct move_t propose_opening()
{
  black_SE_possibilities();
  index_opening = 1;
  int num_vertices = player_graph->num_vertices;
  int opening_Vertex = black_starting_move();

  int opening_voisins[num_vertices];
  voisin_initialisation(opening_voisins);
  voisins_valables(opening_Vertex, opening_voisins);
  int real_opening_voisin = first_voisins(opening_voisins);
  //current_Vertex_mem = real_opening_voisin;
  
  size_t first = (size_t)real_opening_voisin;
  
  jok_Fmove_mem.m = first;

  jok_Fmove_mem.c = BLACK;
  struct move_t first_move = { .m = first };
  first_move.c = BLACK;  
  return first_move;

}

int accept_opening(const struct move_t opening)
{
  graph_updatee(player_graph, opening);
  
  return 1;
}


void initialize_graph(struct graph_t* graph)
{
  assert(graph != NULL);
  player_graph = graph;
  srand(time(NULL));
}


void initialize_color(enum color_t id)
{

  player_id = id;
  if ((index_opening == 1) && (id == BLACK))
    {
	graph_updatee(player_graph, jok_Fmove_mem);
	current_Vertex_mem = jok_Fmove_mem.m;
    }
}

int index_start_rand = 0;

struct move_t play(struct move_t previous_move)
{
  graph_updatee(player_graph, previous_move);

  size_t next;
  
  if ((index_start_rand == 1) || ((int)previous_move.m == last_ending_move))
    {
      index_start_rand = 1;
      //printf("joue au hasard(dejà occupé par l'autre joueur : \n");
      next = next_move_rand();
    }
  else{
  
  next = next_move();

  if (avaible_to_play(next) == 0)
    {
      //printf("joue au hasard(dejà occupé par le même joueur ) : \n");
      next = next_move_rand();
    }
  }
  
  current_Vertex_mem = next;
  struct move_t next_movee = { .m = next };
  next_movee.c = player_id;
  
  graph_updatee(player_graph, next_movee);
  //printf("player_id : %d\n", player_id);
  //
  return next_movee;
}


void finalize()
{
  free(white_ends);
  free(white_starts);
  free(whites);
  free(black_ends);
  free(black_starts);  
  gsl_spmatrix_free(player_graph->t);
  gsl_spmatrix_free(player_graph->o);
  free(player_graph);
}
