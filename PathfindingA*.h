#include "Initialisation.h"

typedef struct noeud_s noeud_t;
typedef struct l_noeud_s l_noeud;
typedef struct liste_s liste;

struct noeud_s{
  int x , y;
  float cout_g,cout_h,cout_f;
  l_noeud *parent; //parent
  //cout_g cout du point de départ au noeud actuel
  //cout_h cout du noeud actuel a point d'arrivée
  //cout_f somme des précendents 
};

 struct l_noeud_s{
  noeud_t noeud;
  l_noeud *suivant;
};

struct liste_s{
  l_noeud *premier;
};

double distance_noeud (noeud_t n1 ,noeud_t n2);
l_noeud* meilleur_noeud(liste *l);
noeud_t noeud_liste(liste *l ,noeud_t n);
void ajouter_liste(liste *l,noeud_t n);
void afficher(liste *l);
void supprimer(liste *l, noeud_t n);
bool deja_present_liste(liste *l,noeud_t n);
void ajouter_cases_adj(liste *lF ,liste *lO,case_t map[21][21],l_noeud *n,noeud_t nA);
liste* recherche_chemin(case_t map[21][21], int departX, int departY ,int  arriveeX , int arriveeY);
liste* liste_chemin_trouver(liste *l);
void ajouter_debut_liste(liste *l,noeud_t n);
