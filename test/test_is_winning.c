#include "graph_operation.h"

//Test la fonction is winning avec en paramètre une liste de valeur à initialiser à 1 dans le tableau "o", le resultat attendu et le titre du test
//Réinitialise à 0 en fin de programme les valeurs de marquage et des pères.
void test_is_winning(size_t* coord,size_t len_init,int res,char* message, size_t src,int color,size_t* dst, size_t len_dst, size_t len_graph)
{
  struct graph_t* graph = malloc(sizeof(struct graph_t));
  square_graph_construct((int)len_graph-1,graph);
  size_t fathers[graph->num_vertices];
  size_t marks[graph->num_vertices];
  for (size_t i = 0 ; i < graph->num_vertices; i++)
    {
      fathers[i] = 0;
      marks[i] = 0;
    }
  for (size_t idx1 = 0 ; idx1 < graph->num_vertices; idx1++)
    {
      gsl_spmatrix_set(graph->o,color,idx1,0);
    }
  for (size_t idx2 = 0 ; idx2 < len_init ; idx2++)
    {
      gsl_spmatrix_set(graph->o,color,coord[idx2],1);
    }
  if (is_winning(src,marks,graph,fathers,color,dst,len_dst) == res)
    {
      printf("%s",message);
      printf(" : SUCCESS\n");
    }
  else
    {
      printf("%s",message);
      printf(" : FAIL\n");
    }
  graph_free(graph);
}



int test_who_win(size_t** games,int* lens,int size,int expected,int shape)
{
  struct graph_t * graph = malloc(sizeof(struct graph_t));
  graph_construction(size-1,shape,graph);
  //printf_spmatrix(graph->o);
  size_t sources[2] = {(size_t)-1,(size_t)-1};
  init_sources(sources,0,size);
  size_t dst0[size-1];
  size_t dst1[size-1];
  size_t* destinations[2] = {dst0,dst1};
  init_destinations(destinations,0,size);
  for (int i = 0 ; i < size-1 ; i++)
    {
      printf(" %zu et %zu \n ", dst0[i],dst1[i]);
    }
  for (int idx = 0 ; idx < 2 ; idx++)
    {
      for(int move = 0 ; move < lens[idx] ; move++)
	{
	  gsl_spmatrix_set(graph->o,idx,games[idx][move],1);
	}
    }
  //printf_spmatrix(graph->o);
  //printf_spmatrix(graph->t);
  int res = who_win(sources,graph,destinations,size-1);
  if (expected == res)
    {
      printf("Test : SUCCESS\n");
      free(graph);
      return 0;
    }
  else
    {
      printf("Test : FAIL\n");
      printf("res == %d\n",res);
      free(graph);
      return 0;
    }
}

int main()
{
  printf("------------------Tests sur un graph carré 4*4---------------------------------------\n");
  size_t len_dst = 4;
  size_t dst[len_dst];
  for (size_t idx = 0; idx < len_dst ; idx++)
    {
      dst[idx] = (len_dst - 1) * len_dst + idx;
    }
  size_t coord1[8] = {0,1,2,3,12,13,14,15};
  size_t coord2[9] = {0,1,2,3,12,13,14,15,5};
  size_t coord3[10] = {0,1,2,3,12,13,14,15,5,10};
  size_t coord4[10] = {0,1,2,3,12,13,14,15,5,9};
  size_t coord5[11] = {0,1,2,3,12,13,14,15,5,6,7};
  size_t coord6[11] = {0,1,2,3,12,14,15,5,6,7,9};
  test_is_winning(coord1,8,0,"Test 1",0,0,dst, len_dst,4);
  test_is_winning(coord2,9,0,"Test 2",0,0,dst, len_dst,4);
  test_is_winning(coord3,10,0,"Test 3",0,0,dst, len_dst,4);
  test_is_winning(coord4,10,1,"Test 4",0,0,dst, len_dst,4);
  test_is_winning(coord4,10,1,"Test 5",3,0,dst, len_dst,4);
  test_is_winning(coord5,11,0,"Test 6",3,0,dst, len_dst,4);
  test_is_winning(coord6,11,0,"Test 7",3,0,dst, len_dst,4);
  printf("------------------Tests sur un graph carré 6*6---------------------------------------\n");
  size_t dst1[1];
  dst1[0] = 34;
  size_t coord7[19] = {1,2,8,9,10,11,13,14,15,16,17,18,19,20,23,25,28,29,34};
  test_is_winning(coord7,19,1,"Test 1",1,0,dst1,1,6);
  size_t coord8[18] = {1,2,8,9,10,11,13,14,15,16,17,18,19,20,23,25,29,34};
  test_is_winning(coord8,18,0,"Test 2",1,0,dst1,1,6);
  printf("-----------------tests qui annoncent le gagnant------------------------------------\n");
  int len0_1 =1;
  size_t game0_1[1] = {6};
  int len1_1 = 3;
  size_t game1_1[3] = {11,12,13};

  size_t * games1[2] = {game0_1,game1_1};
  int lens1[2] = {len0_1,len1_1};
  int size1 = 5;
  int shape1 = 0;
  test_who_win(games1,lens1,size1,1,shape1);
  int len0_2 =1;
  size_t game0_2[1] = {6};
  int len1_2 = 2;
  size_t game1_2[2] = {11,12};
  size_t * games2[2] = {game0_2,game1_2};
  int lens2[2] = {len0_2,len1_2};
  int size2 = 5;
  int shape2 = 0;
  test_who_win(games2,lens2,size2,-1,shape2);
  int len0_3 =3;
  size_t game0_3[3] = {7,12,18};
  int len1_3 = 4;
  size_t game1_3[4] = {11,13,16,17};
  size_t * games3[2] = {game0_3,game1_3};
  int lens3[2] = {len0_3,len1_3};
  int size3 = 5;
  int shape3 = 1;
  test_who_win(games3,lens3,size3,1,shape3);
  return 0;
}
