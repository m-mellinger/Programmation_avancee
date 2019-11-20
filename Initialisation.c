#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Affichage.h"


void init_data(world_t *world){
  world->fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH ,SCREEN_HEIGHT, 0);
  
  world->positionX = 0;
  world->positionY = 0;
  
  world->positionPersoX = world->positionX+10;
  world->positionPersoY = world->positionY+10;
  
  sprintf(world->fichier, "Map.txt");
  
  world->renderer= SDL_CreateRenderer(world->fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  init_tab_map(world);
}
