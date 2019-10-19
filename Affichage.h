#include "Initialisation.h"

int nb_colonne(const char* nomFichier);
int nb_ligne(const char* nomFichier); 
void tab_map(const char* nomFichier,world_t *world);
int conv_char_en_entier(char s);
void afficher_jeu(world_t *world);
void deplacerDroite(world_t *world);
void deplacerBas(world_t *world);
void deplacerHaut(world_t *world);
void deplacerGauche(world_t *world);
