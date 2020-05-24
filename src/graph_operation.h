#ifndef _GRAPH_OPERATION_
#define _GRAPH_OPERATION_

//omar


#include "graph.h"
#include "move.h"
#include "player.h"


void square_graph_construct(int size, struct graph_t* graph );
void hexa_graph_construct(int size, struct graph_t* graph);
void graph_construction(int size, int graph_shape, struct graph_t* graph);
//void graph_copy_function(struct graph_t* dest,struct graph_t* src);
struct graph_t * graph_copy_function(struct graph_t * src, int n);
void graph_update(struct graph_t* graph, struct move_t move);
void graph_free(struct graph_t *g);
int is_winning(size_t ,size_t*, struct graph_t*,size_t*,int,size_t*, size_t);
void printf_spmatrix(gsl_spmatrix*);
int init_sources(size_t* ,int ,int);
int init_destinations( size_t** ,int ,int );
int who_win(size_t * , struct graph_t* , size_t ** ,int );
#endif



