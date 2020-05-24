#ifndef DJIPLAYER_H
#define DJIPLAYER_H

#include <graph.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "server.h"

#define MAX_NUMV 20

//static enum color_t player_id = NO_COLOR;
static enum color_t player_id = NO_COLOR;
static struct graph_t* player_graph = NULL;


void black_SE_possibilities();
int black_ending_move();
int black_starting_move();
void white_SE_possibilities();
int white_ending_move();
int white_starting_move();
void voisin_initialisation(int* vrai_voisins);
void is_visited_initialisation(int* is_visited);
int still_Vertex(int* is_visited);
int pas_voisins(int* voisins_valides);
int first_voisins(int* voisins_valides);
int min_Vertex_distance(int* dist, int* is_visited);
void maj_distances(int s1, int s2, int* dist, int* prev);
void djikstra(int starting_Vertex, int* dist, int* is_visited, int* voisins, int* prev);
void path_initialisation(int* path);
void prev_initialisation(int* prev);
int path_construct(int* path,int* prev,int* dist, int* is_visited,int* voisins, int starting_Vertex, int end_Vertex);
size_t next_move_rand();
size_t next_move();
  
#endif

