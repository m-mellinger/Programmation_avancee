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


struct groupeMonstre_s{
  monstre_t* tab[NB_MONSTRE];
  int posX_maleAlpha;
  int posY_maleAlpha;
};
typedef struct groupeMonstre_s groupeMonstre_t;

struct personnage_s{
  int positionX; // position du personnage dans le monde
  int positionY;
  int vie;
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
  char fichier[200];
  personnage_t personnage;
  groupeMonstre_t groupe1;
  groupeMonstre_t groupe2;
};
typedef struct world_s world_t;

void init_data(world_t *world);
