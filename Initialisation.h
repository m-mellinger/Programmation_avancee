
#define SCREEN_WIDTH 840
#define SCREEN_HEIGHT 924
#define PLAYSCREEN_HEIGHT 840
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


struct world_s{
  int positionX; // position dans le fichier txt
  int positionY;
  SDL_Window* fenetre;
  SDL_Renderer* renderer;
  char tab[SCREEN_HEIGHT/40][SCREEN_WIDTH/40];
  int positionPersoX; // position du personnage dans le monde
  int positionPersoY;
  char fichier[200];
  groupeMonstre_t groupe1;
  groupeMonstre_t groupe2;
};
typedef struct world_s world_t;

void init_data(world_t *world);
