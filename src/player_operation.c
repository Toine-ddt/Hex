#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "player_def.h"
#include "graph_operation.h"

//charge dynamiquement les fonctions, renvoie un bouléen qui indique si cela s'est bien déroulé
int initialize_player(struct player* player, void* player_lib)
{
  char* error;
  dlerror();
  player->functions.initialize_graph = dlsym(player_lib, "initialize_graph");
  error = dlerror();
  if (error != NULL)
    {
      printf("Erreur : %s\n", error);
      return 0;
    }
  dlerror();
  player->functions.get_player_name = dlsym(player_lib, "get_player_name");
  error = dlerror();
  if (error != NULL)
    {
      printf("Erreur : %s\n", error);
      return 0;
    }
  dlerror();
  player->functions.propose_opening = dlsym(player_lib, "propose_opening");
  error = dlerror();
  if (error != NULL)
    {
      printf("Erreur : %s\n", error);
      return 0;
    }
  dlerror();
  player->functions.accept_opening = dlsym(player_lib, "accept_opening");
  error = dlerror();
  if (error != NULL)
    {
      printf("Erreur : %s\n", error);
      return 0;
    }
  dlerror();
  player->functions.initialize_color = dlsym(player_lib, "initialize_color");
  error = dlerror();
  if (error != NULL)
    {
      printf("Erreur : %s\n", error);
      return 0;
    }
  dlerror();
  player->functions.play = dlsym(player_lib, "play");
  error = dlerror();
  if (error != NULL)
    {
      printf("Erreur : %s\n", error);
      return 0;
    }
  dlerror();
  player->functions.finalize = dlsym(player_lib, "finalize");
  error = dlerror();
  if (error != NULL)
    {
      printf("Erreur : %s\n", error);
      return 0;
    }
  return 1;
}

void player_free(struct player* player)
{
  //graph_free(player->player_graph);
  //free(player->functions
  free(player);
  
}
