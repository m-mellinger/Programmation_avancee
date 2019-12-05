#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define SCREEN_WIDTH 840
#define PLAYSCREEN_HEIGHT 735
#define SCREEN_HEIGHT PLAYSCREEN_HEIGHT+0.1*PLAYSCREEN_HEIGHT
#define NB_MONSTRE 3


struct monstre_s{
  int posMx;
  int posMy;
  int pdvM;
};
typedef struct monstre_s monstre_t;

struct personnage_s{
  int positionX; // position du personnage dans le monde
  int positionY;
  int vie;
  int orientation;
};
typedef struct personnage_s personnage_t;

struct case_s{
  int accessible;
  int background;
  int obstacle;
  int typeObstacle;
  int monstre;
  int typeMonstre;
};
typedef struct case_s case_t;

struct world_s{
  int positionX; // position dans le fichier txt
  int positionY;
  SDL_Window* fenetre;
  SDL_Renderer* renderer;
  case_t tab[21][21];
  char nomFichier[200];
  personnage_t personnage;
  monstre_t monstre; 
  SDL_RWops* fichier;
  SDL_Surface *pavage;
  SDL_Surface *Tpersonnage;
  SDL_Surface *vie;
  SDL_Surface *pixilFrame;
  SDL_Surface *Tmonstre;
};
typedef struct world_s world_t;

void init_data(world_t *world);
void libererWorld(world_t *world);
