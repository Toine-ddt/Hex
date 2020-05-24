#include "graph_operation.h"
#include "graph.h"

//omar

void square_graph_construct(int size, struct graph_t* graph )
{
  int NBR_VERTICES = (size + 1)*(size + 1);
  graph->num_vertices = NBR_VERTICES;
 
  gsl_spmatrix *matrice_adja=gsl_spmatrix_alloc(NBR_VERTICES,NBR_VERTICES);
  gsl_spmatrix *matrice_o=gsl_spmatrix_alloc(2,NBR_VERTICES);
  
  //gsl_matrix_set_zero(matrice_adja);
  //gsl_matrix_set_zero(matrice_o);
  /*---------------------remplissage--------------*/
  
  for(int i=0;i<size*(size+1);i++)
    {
      gsl_spmatrix_set(matrice_adja,i,i+1,1);
      gsl_spmatrix_set(matrice_adja,i,i+size+1,1);
    }

/*--------cote droit-------------*/

  for(int i=1;i<size+1;i++)
    gsl_spmatrix_set(matrice_adja,i*(size+1)-1,i*(size+1),0);

 /*-----cote bas-----*/
  for(int i=size*(size+1);i<size*(size+2);i++)
    {
      gsl_spmatrix_set(matrice_adja,i,i+1,1);
    }

  /*------matrice symetrique------*/
  for(int i=0;i<(size+1)*(size+1);i++)
    {
      for(int j=i+1;j<(size+1)*(size+1);j++)
	{
	  gsl_spmatrix_set(matrice_adja,j,i,gsl_spmatrix_get(matrice_adja,i,j));
	}
    }

  /*---------matrice_o---------*/
  for(int i=0;i<size;i++)
    {
      gsl_spmatrix_set(matrice_o,0,i,1);
      gsl_spmatrix_set(matrice_o,1,(i+1)*(size+1),1);
      gsl_spmatrix_set(matrice_o,1,(i+1)*(size+1)-1,1);
    }
  for(int i=size*(size+1)+1;i<=size*(size+2);i++)
    gsl_spmatrix_set(matrice_o,0,i,1);

  /*---fin du remplissage---*/
  
  graph->t=matrice_adja;
  graph->o=matrice_o;
 
}

/*-----------------initialiser le graph-----------------------*/
void hexa_graph_construct(int size, struct graph_t* graph)
{
  int NBR_VERTICES = (size + 1)*(size + 1);
  graph->num_vertices=NBR_VERTICES;
 
  gsl_spmatrix *matrice_adja=gsl_spmatrix_alloc(NBR_VERTICES,NBR_VERTICES);
  gsl_spmatrix *matrice_o=gsl_spmatrix_alloc(2,NBR_VERTICES);
  
  // gsl_matrix_set_zero(matrice_adja);
  //gsl_matrix_set_zero(matrice_o);
  /*---------------------cas d'un graphe hexagonal--------------*/
  
  for(int i=0;i<size*(size+1);i++)
    {
      gsl_spmatrix_set(matrice_adja,i,i+1,1);
      gsl_spmatrix_set(matrice_adja,i,i+size,1);
      gsl_spmatrix_set(matrice_adja,i,i+size+1,1);
    }

  gsl_spmatrix_set(matrice_adja,0,size,0);
  
  /*-------coté gauche----------*/
  for(int i=1;i<size;i++)
    gsl_spmatrix_set(matrice_adja,i*(size+1),i*(size+1)+size,0);
  /*--------cote droit-------------*/

  for(int i=1;i<size+1;i++)
    gsl_spmatrix_set(matrice_adja,i*(size+1)-1,i*(size+1),0);

  /*-----cote bas-----*/
  for(int i=size*(size+1);i<size*(size+2);i++)
    {
      gsl_spmatrix_set(matrice_adja,i,i+1,1);
    }

  /*------matrice symetrique------*/
  for(int i=0;i<(size+1)*(size+1);i++)
    {
      for(int j=i+1;j<(size+1)*(size+1);j++)
	{
	  gsl_spmatrix_set(matrice_adja,j,i,gsl_spmatrix_get(matrice_adja,i,j));
	}
    }

  /*---------matrice_o---------*/
  for(int i=0;i<size;i++)
    {
      gsl_spmatrix_set(matrice_o,0,i,1);
      gsl_spmatrix_set(matrice_o,1,(i+1)*(size+1),1);
      gsl_spmatrix_set(matrice_o,1,(i+1)*(size+1)-1,1);
    }
  for(int i=size*(size+1)+1;i<=size*(size+2);i++)
    gsl_spmatrix_set(matrice_o,0,i,1);

  /*---fin du remplissage---*/
  
  graph->t=matrice_adja;
  graph->o=matrice_o;
  
}




void graph_construction(int size, int graph_shape, struct graph_t* graph)
{
  if (graph_shape == 0) // we use zero for square before creating an enum for that
    {
      square_graph_construct(size, graph);
    }
  else if (graph_shape == 1)
    hexa_graph_construct(size, graph);
  else{
    printf("\nwe still don't have this shape of graph\n");
  }
}


struct graph_t * graph_copy_function(struct graph_t * src, int n){ 
//aloowing the memory for the copy
  struct graph_t * copy = malloc(sizeof(struct graph_t));
  copy->num_vertices=src->num_vertices;
  n++;
  //copy the o and t matrixes
  gsl_spmatrix *t_c= gsl_spmatrix_alloc(n*n,n*n);
  gsl_spmatrix *o_c = gsl_spmatrix_alloc(2,n*n);
  gsl_spmatrix_memcpy(t_c,(const gsl_spmatrix *)src->t);
  gsl_spmatrix_memcpy(o_c,(const gsl_spmatrix *)src->o);
  copy->t=t_c;
  copy->o=o_c;
  return copy;
}


/*
void graph_copy_function(struct graph_t* dest, struct graph_t* src)
{
  //int gsl_spmatrix_memcpy(gsl_spmatrix * dest, const gsl_spmatrix * src)
  printf("adresse de dest = %p\n",dest);
  dest->num_vertices = src->num_vertices;
  gsl_spmatrix * t = gsl_spmatrix_alloc(src->num_vertices, src->num_vertices);
  gsl_spmatrix * o = gsl_spmatrix_alloc(2,src->num_vertices);
  gsl_spmatrix_memcpy(o, (const gsl_spmatrix *)src->o);
  gsl_spmatrix_memcpy(t, (const gsl_spmatrix *)src->t);
  dest->t = t;
  dest->o = o;
}
*/

void graph_update(struct graph_t* graph, struct move_t move)
{
  gsl_spmatrix_set(graph->o, move.c, move.m, 1);
}


void graph_free(struct graph_t *g)
{
  gsl_spmatrix_free(g->t);
  gsl_spmatrix_free(g->o);
  free(g);
}


//Affichage d'une gsl_spmatrix
void printf_spmatrix(gsl_spmatrix* t)
{
  printf("[");
  printf("[%f",gsl_spmatrix_get(t,0,0));
  for (size_t j = 1; j < t->size2; j++)
    {
      printf(",%f",gsl_spmatrix_get(t,0,j));
    }
  printf("]\n");
  for (size_t i = 1; i < t->size1; i++)
    {
      printf(",[%f",gsl_spmatrix_get(t,i,0));
      for (size_t j = 1; j < t->size2; j++)
	{
	  printf(",%f",gsl_spmatrix_get(t,i,j));
	}
      printf("]\n");
    }
  printf("]\n");
}

size_t belong(size_t element, size_t* tab,size_t len)
{
  for (size_t idx= 0; idx < len ; idx++)
    {
      if (element == tab[idx])
	{
	  return 1;
	}
    }
  return 0;
}


//Algorithme de parcours en profondeur
// Marque les voisins du sommet source de manière récursive
//Enregistre pour chaque sommet son père.
//L'algorithme se stoppe dès qu'un chemin valide est trouvé
int is_winning(size_t src,size_t* marks, struct graph_t* graph,size_t* fathers,int color,size_t* dst, size_t len_dst)
{
  int res = 0;
  marks[src] = 1;
  for(size_t vertice = 0 ; vertice < graph->num_vertices; vertice++)
    {
      //printf("%lf\n",gsl_spmatrix_get(graph->t, vertice, src));
      double is_neighboor = (gsl_spmatrix_get(graph->t, vertice, src) * gsl_spmatrix_get(graph->o,color,vertice));
      //printf("is_neighboor == %f\n",is_neighboor);
      if (is_neighboor !=0 )
	{
	  //printf("Numero sommet == %lu\n",vertice);
	  if ( belong(vertice,dst,len_dst) == 1)
	    {
	      //printf("appartenance aux destinations\n");
	      fathers[vertice] = src;
	      return 1;
	    }
	  else
	    if (marks[vertice] == 0)
	    {
	      fathers[vertice] = src;
	      res = is_winning(vertice,marks,graph,fathers,color,dst,len_dst);
	      if (res == 1)
		{
		  return 1; 
		}
	    }
	}
    }
  return res;
}

//initialise les sommets à partir desquels on commence à chercher un chemin gagnant dans le plateau.
//Cela s'effectue pour chacun des joueurs
int init_sources(size_t* sources,int graph_shape,int size)
{
  if (graph_shape == 0)
    {
      sources[0] = 0;
      sources[1] = size; 
    }
  else if (graph_shape == 1)
    {
      sources[0] = 0;
      sources[1] = size;
    }
  return 0;
}

//Initialistion des sommets valides à atteindre pour gagner
//Cela s'effectue pour chacun des joueurs.
int init_destinations( size_t** destinations,int graph_shape,int size)
{
  size_t idx0 = 0;
  size_t idx1 = 0;
  if (graph_shape == 0)
    {
      for(int i=0;i<size-1;i++)
	{
	  destinations[1][idx1] = (i+1)*(size) -1;
	  idx1++;
	}
      for(int i=(size-1)*(size)+1;i<=(size-1)*(size+1);i++)
	{
	  destinations[0][idx0] = i;
	  idx0++;
	}
    }
  else if (graph_shape == 1)
	{
	  for(int i=0;i<size-1;i++)
	    {
	      destinations[1][idx1] = (i+1)*(size)-1;
	      idx1++;
	    }
	  for(int i=(size-1)*(size)+1;i<=(size-1)*(size+1);i++)
	    {
	      destinations[0][idx0] = i;
	      idx0++;
	    }
	}
  //printf("idx0 == %zu et idx1 == %zu\n",idx0,idx1);
  return 0;
}

//Parcours la liste des joueur pour tester si l'un d'eux possède un chemin gagnant.
//Si l'un gagne , la fonction renvoie son numero, sinon elle renvoie -1
int who_win(size_t * sources, struct graph_t* graph, size_t ** destinations,int size)
{
  for (int player = 0 ; player < 2 ; player++)
    {
      size_t* marks = malloc(sizeof(size_t)*graph->num_vertices);
      size_t* fathers = malloc(sizeof(size_t)*graph->num_vertices);
      for (size_t vertice = 0 ; vertice < graph->num_vertices ; vertice++)
	{
	  marks[vertice] = 0;
	  fathers[vertice] = 0;
	}
      if (is_winning(sources[player],marks,graph,fathers,player,destinations[player],size))
	{
	  free(marks);
	  free(fathers);
	  //printf("fin test joueur %d\n",player);
	  return player;
	}
      free(marks);
      free(fathers);
      //printf("fin test joueur %d\n",player);
    }
  return -1;
}
