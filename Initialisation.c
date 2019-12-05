#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Affichage.h"


void init_data(world_t *world){
  world->fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH ,SCREEN_HEIGHT, 0);
  
  world->positionX = 0;
  world->positionY = 0;

  world->monstre.posMx = world->positionX;
  world->monstre.posMy = world->positionY;
   
  world->personnage.positionX = world->positionX+10;
  world->personnage.positionY = world->positionY+10;
  world->personnage.vie = 100; 
  
  sprintf(world->nomFichier, "Map.txt");
  
  world->fichier = SDL_RWFromFile(world->nomFichier,"r");

  world->Tpersonnage =SDL_LoadBMP("personnage.bmp");
  Uint32 colorkey = SDL_MapRGB(world->Tpersonnage->format, 0, 255, 255 );
  SDL_SetColorKey(world->Tpersonnage,1,colorkey);

  world->pavage = SDL_LoadBMP("pavage.bmp");

  world->vie =  SDL_LoadBMP("vie.bmp");

  world->pixilFrame = SDL_LoadBMP("pixil-frame.bmp");

  world->Tmonstre = SDL_LoadBMP("sprites.bmp");
  colorkey = SDL_MapRGB(world->Tmonstre->format, 0, 255, 255 );
  SDL_SetColorKey(world->Tmonstre,1,colorkey);
  
  world->renderer= SDL_CreateRenderer(world->fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  
  init_tab_map(world);
}

void libererWorld(world_t *world){
  SDL_FreeSurface(world->Tpersonnage);
  SDL_FreeSurface(world->pavage);
  SDL_FreeSurface(world->vie);
  SDL_FreeSurface(world->pixilFrame);
  SDL_FreeSurface(world->Tmonstre);
  SDL_RWclose(world->fichier);
}
