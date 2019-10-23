
#define SCREEN_WIDTH 840
#define SCREEN_HEIGHT 840

struct world_s{
  int positionX; // position dans le fichier txt
  int positionY;
  SDL_Window* fenetre;
  SDL_Renderer* renderer;
  char tab[SCREEN_HEIGHT/40][SCREEN_WIDTH/40];
  int positionPersoX; // position du personnage dans le monde
  int positionPersoY;
  char fichier[200];
};
typedef struct world_s world_t;

void init_data(world_t *world);
