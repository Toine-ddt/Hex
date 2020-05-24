#include <stdlib.h>
#include<stdio.h>
#include"graph.h"
#include"graph_operation.h"

/*-------fais la somme de la colonne n--------------*/

int nbr_voisins_sn(struct graph_t *g, int n,int size)
{
      int s=0;
      for(int j=0;j<(size+1)*(size+1);j++)
	  s=s+gsl_spmatrix_get(g->t,j,n);
      return s;
}
  

int main(int argc, char * argv[])
{
  //int m=atoi(argv[1]);
  
  int m=7;
  struct graph_t * g=malloc(sizeof(struct graph_t));
  square_graph_construct(m,g);

  printf("-----------------RESULTATS--TESTS----------------\n\n");




  printf("------------Tests-sur-un-graphe-carré------------\n\n");
  
  int c=0;
  int d=0;
  printf("Le sommet %d a 2 voisins : %s\n",0,( (nbr_voisins_sn(g,0,m)==2)? "SUCCESS" : "FAILED"));
  ++d;
  if(nbr_voisins_sn(g,0,m)==2)
    ++c;
  
  printf("Le sommet %d a 2 voisins : %s\n",m,( (nbr_voisins_sn(g,m,m)==2)? "SUCCESS" : "FAILED"));
  ++d;
  if(nbr_voisins_sn(g,m,m)==2)
    ++c;



  
  printf("Le sommet %d a 2 voisins : %s\n",m*(m+1),( (nbr_voisins_sn(g,m*(m+1),m)==2)? "SUCCESS" : "FAILED"));
  ++d;
  if(nbr_voisins_sn(g,m*(m+1),m)==2)
    ++c;


  printf("Le sommet %d a 2 voisins : %s\n",(m+1)*(m+1) -1,( (nbr_voisins_sn(g,(m+1)*(m+1) -1,m)==2)? "SUCCESS" : "FAILED"));
  ++d;
  if(nbr_voisins_sn(g,(m+1)*(m+1)-1,m)==2)
    ++c;

  
  for(int k=1;k<m;k++)
    {
      printf("Le sommet n %d a 3 voisins : %s\n",k, ( (nbr_voisins_sn(g,k,m)==3)? "SUCCESS" : "FAILED"));
      ++d;
      if(nbr_voisins_sn(g,k,m)==3)
	++c;

      
      printf("Le sommet n %d a 3 voisins : %s\n",k*(m+1), ( (nbr_voisins_sn(g,k*(m+1),m)==3)? "SUCCESS" : "FAILED"));
      ++d;
      if(nbr_voisins_sn(g,k*(m+1),m)==3)
	++c;


      printf("Le sommet n %d a 3 voisins : %s\n",(k+1)*(m+1)-1, ( (nbr_voisins_sn(g,(k+1)*(m+1)-1,m)==3)? "SUCCESS" : "FAILED"));
      ++d;
      if(nbr_voisins_sn(g,(k+1)*(m+1)-1,m)==3)
	++c;


      printf("Le sommet n %d a 3  voisins : %s\n",m*m+m+k, ( (nbr_voisins_sn(g,m*m+m+k,m)==3)? "SUCCESS" : "FAILED"));
      ++d;
      if(nbr_voisins_sn(g,m*m+m+k,m)==3)
	++c;


    }

  printf("Le sommet n %d a 4 voisins : %s\n\n",m+2, ( (nbr_voisins_sn(g,m+2,m)==4)? "SUCCESS" : "FAILED"));
  ++d;
  if(nbr_voisins_sn(g,m+2,m)==4)
    ++c;



  printf("-------------------RESULTAT: %d / %d  ----------------\n\n",c,d);

  /*----------test sur un graphe hexagonel--------------------------------*/
  
  printf("------------Tests-sur-un-graphe-hexagonal------------\n\n");

  struct graph_t * h=malloc(sizeof(struct graph_t));
  hexa_graph_construct(m,h);
  
  int cmp1=0;
  int cmp2=0;
  printf("Le sommet %d a 2 voisins : %s\n",0,( (nbr_voisins_sn(h,0,m)==2)? "SUCCESS" : "FAILED"));
  ++cmp1;
  if(nbr_voisins_sn(h,0,m)==2)
    ++cmp2;
  
  printf("Le sommet %d a 3 voisins : %s\n",m,( (nbr_voisins_sn(h,m,m)==3)? "SUCCESS" : "FAILED"));
  ++cmp1;
  if(nbr_voisins_sn(h,m,m)==3)
    ++cmp2;



  
  printf("Le sommet %d a 3 voisins : %s\n",m*(m+1),( (nbr_voisins_sn(h,m*(m+1),m)==3)? "SUCCESS" : "FAILED"));
  ++cmp1;
  if(nbr_voisins_sn(h,m*(m+1),m)==3)
    ++cmp2;


  printf("Le sommet %d a 2 voisins : %s\n",(m+1)*(m+1)-1,( (nbr_voisins_sn(h,(m+1)*(m+1)-1,m)==2)? "SUCCESS" : "FAILED"));
  ++cmp1;
  if(nbr_voisins_sn(h,(m+1)*(m+1)-1,m)==2)
    ++cmp2;

  
  for(int k=1;k<m;k++)
    {
      printf("Le sommet n %d a 4 voisins : %s\n",k, ( (nbr_voisins_sn(h,k,m)==4)? "SUCCESS" : "FAILED"));
      ++cmp1;
      if(nbr_voisins_sn(h,k,m)==4)
	++cmp2;

      
      printf("Le sommet n %d a 4 voisins : %s\n",k*(m+1), ( (nbr_voisins_sn(h,k*(m+1),m)==4)? "SUCCESS" : "FAILED"));
      ++cmp1;
      if(nbr_voisins_sn(h,k*(m+1),m)==4)
	++cmp2;


      printf("Le sommet n %d a 4 voisins : %s\n",(k+1)*(m+1)-1, ( (nbr_voisins_sn(h,(k+1)*(m+1)-1,m)==4)? "SUCCESS" : "FAILED"));
      ++cmp1;
      if(nbr_voisins_sn(h,(k+1)*(m+1)-1,m)==4)
	++cmp2;


      printf("Le sommet n %d a 4  voisins : %s\n",m*m+m+k, ( (nbr_voisins_sn(h,m*m+m+k,m)==4)? "SUCCESS" : "FAILED"));
      ++cmp1;
      if(nbr_voisins_sn(h,m*m+m+k,m)==4)
	++cmp2;


    }

  printf("Le sommet n %d a 6 voisins : %s\n\n",m+2, ( (nbr_voisins_sn(h,m+2,m)==6)? "SUCCESS" : "FAILED"));
  ++cmp1;
  if(nbr_voisins_sn(h,m+2,m)==6)
    ++cmp2;



  printf("-------------------RESULTAT: %d / %d  ----------------\n\n",cmp2,cmp1);

  graph_free(g);
  graph_free(h);

  return 0;

  
}

      
      
  
