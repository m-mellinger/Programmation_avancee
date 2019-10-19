struct world_s{
  int positionX; // position du personnage dans le monde 
  int positionY;
  SDL_Window* fenetre;
  SDL_Renderer* renderer;
  char** tab[21][21];
  
};
typedef struct world_s world_t;

void init_data(world_t *world);
