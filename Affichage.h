#include "Initialisation.h"
#include "PathfindingA*.h"

int nb_colonne(world_t *world);
int nb_ligne(world_t *world); 
void init_tab_map(world_t *world);
int conv_char_en_entier(char s);
void afficher_jeu(world_t *world);
void deplacerDroite(world_t *world);
void deplacerBas(world_t *world);
void deplacerHaut(world_t *world);
void deplacerGauche(world_t *world);
void deplacementAuto(world_t *world,liste *l);
