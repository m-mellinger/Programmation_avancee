#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Affichage.h"

#define SCREEN_WIDTH 840
#define SCREEN_HEIGHT 840


int main(int argc, char *argv[])
{
  SDL_Window* fenetre; // Déclaration de la fenêtre
  SDL_Event evenements; // Événements liés à la fenêtre
  bool terminer = false;

  SDL_Renderer* renderer;
  SDL_Texture *bitmapTex;
  SDL_Surface *bitmapSurface;

  
  if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
      printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
      SDL_Quit();
      return EXIT_FAILURE;
    }
  // Créer la fenêtre
  fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,
			     SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH ,SCREEN_HEIGHT, 0);
  if(fenetre == NULL) // En cas d’erreur
    {
      printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
      SDL_Quit();
      return EXIT_FAILURE;
    }

  afficher_jeu(fenetre);
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
	      case SDLK_s:
	      case SDLK_q:
	      case SDLK_d:

	      case SDLK_a:
		terminer = true; break;
	      }
	  }
    }
  SDL_DestroyWindow(fenetre);
  SDL_Quit();
  return 0;
}
