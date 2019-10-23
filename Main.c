#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Affichage.h"

int main(int argc, char *argv[])
{
  world_t world;
  SDL_Event evenements; // Événements liés à la fenêtre
  bool terminer = false;
  
  init_data(&world);
  afficher_jeu(&world);
  while(!terminer)
    {
      while( SDL_PollEvent( &evenements ) )
	switch(evenements.type)
	  {
	  case SDL_QUIT:
	    terminer = true; break;
	  case SDL_KEYDOWN:
	    switch(evenements.key.keysym.sym)
	      {
	      case SDLK_ESCAPE:
	      case SDLK_z:
		if ( world.tab[world.positionPersoX][world.positionPersoY-1] != '1'){
		  deplacerHaut(&world);
		  afficher_jeu(&world);
		}
		break;
	      case SDLK_s:
		if ( world.tab[world.positionPersoX][world.positionPersoY+1] != '1'){
		  deplacerBas(&world);
		  afficher_jeu(&world);
		}
		break;
	      case SDLK_q:
		if (world.tab[world.positionPersoX-1][world.positionPersoY] != '1'){
		  deplacerGauche(&world);
		  afficher_jeu(&world);
		}
		break;
	      case SDLK_d:
		if ( world.tab[world.positionPersoX+1][world.positionPersoY] != '1'){
		  deplacerDroite(&world);
		  afficher_jeu(&world);
		}
		break;

	      case SDLK_a:
		terminer = true; break;
	      }
	  }
    }
  SDL_DestroyWindow(world.fenetre);
  SDL_Quit();

  return 0;
}
