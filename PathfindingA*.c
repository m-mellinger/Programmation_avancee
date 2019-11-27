#include "PathfindingA*.h"

double distance_noeud (noeud_t n1 ,noeud_t n2){
  double x;
  x = fabs(n1.x-n2.x)+fabs(n1.y-n2.y);
  return x;
  }

l_noeud* meilleur_noeud(liste *l){
  //printf("test");
  float m_coutF = l->premier->noeud.cout_f;
  l_noeud *n = l->premier;
  l_noeud *actuel = l->premier;
    while (actuel != NULL){
      if (actuel->noeud.cout_f <m_coutF){
	m_coutF = actuel->noeud.cout_f;
	n = actuel;

      }
      actuel = actuel->suivant;
    }
    return n;
  }

noeud_t noeud_liste(liste *l ,noeud_t n){
  l_noeud *actuel = l->premier;
  while (actuel->suivant != NULL){
    if(actuel->noeud.x == n.x && actuel->noeud.y == n.y){
      return actuel->noeud;
    }
    actuel = actuel->suivant;
  }
}

void afficher_noeud(noeud_t *n){
  printf("%d,%d,%f->",n->x,n->y,n->cout_f);
}

void afficher(liste *l){
  l_noeud *actuel = l->premier;
  while ( actuel!= NULL){
    afficher_noeud(&actuel->noeud);
    actuel = actuel->suivant;
  }
  printf("NULL\n");
}

void ajouter_liste(liste *l ,noeud_t n){
  l_noeud *actuel = l->premier;
  l_noeud *prec = actuel;
 
  while (actuel != NULL){
    prec = actuel;
    actuel = actuel->suivant;
    }
  
  l_noeud *nouveau = malloc(sizeof(l_noeud));
  nouveau->noeud = n;
  nouveau->suivant = NULL;
  
  prec->suivant = nouveau;
}

void ajouter_debut_liste(liste *l,noeud_t n){
  l_noeud *nouveau = malloc(sizeof(l_noeud));
  nouveau->noeud = n;
  nouveau->suivant = l->premier;
  l->premier=nouveau;
}


void supprimer(liste *l, noeud_t n){
  l_noeud *actuel = l->premier;
  l_noeud *supprimer;
  if (l->premier->noeud.x == n.x &&  l->premier->noeud.y == n.y){
    supprimer = l->premier;
    l->premier = l->premier->suivant; 
   
  }
  else {
    while(actuel->suivant->noeud.x != n.x || actuel->suivant->noeud.y != n.y){
      actuel = actuel->suivant;
    }
    supprimer = actuel->suivant;
    actuel->suivant= actuel->suivant->suivant; 

  }
}

bool deja_present_liste(liste *l,noeud_t n){
   l_noeud *actuel = l->premier;
   
  while (actuel != NULL){
    if(actuel->noeud.x == n.x && actuel->noeud.y == n.y)
      return true;
    actuel=actuel->suivant;
  }
  return false;
}

void ajouter_cases_adj(liste *lF ,liste *lO,case_t map[21][21],l_noeud *n,noeud_t nA){

  noeud_t *tmp = malloc(sizeof(noeud_t));
  noeud_t *etud = malloc(sizeof(noeud_t));
  for (int i = n->noeud.x-1;i <= n->noeud.x+1;i++){
    for (int j = n->noeud.y-1;j <= n->noeud.y+1;j++){
      if ( map[i][j].accessible == 0 && (((i == n->noeud.x-1 || i ==n->noeud.x+1) && j == n->noeud.y )||((j == n->noeud.y-1 || j ==n->noeud.y+1) && i == n->noeud.x))){ // ne prend pas en compte le noeud actuel pour ne pas boucler ,quand il y a un obstacle sur la map et les diagonales
    	 etud->x = i;
	 etud->y = j;
	 
	 if (!deja_present_liste(lF,*etud)){
	   tmp->cout_g = n->noeud.cout_g + distance_noeud(*etud,n->noeud);
	   tmp->cout_h = distance_noeud(*etud,nA);
	   tmp->cout_f = tmp->cout_g + tmp->cout_h;
	   tmp->parent = n;
	   if (deja_present_liste(lO,*etud)){
	     if(tmp->cout_f < noeud_liste(lO,*etud).cout_f)
	       *etud = noeud_liste(lO,*etud);
	     etud->cout_f = tmp->cout_f;
	   }		
	   else{
	     etud->cout_g = tmp->cout_g;
	     etud->cout_h = tmp->cout_h;
	     etud->cout_f = tmp->cout_f;
	     etud->parent = tmp->parent;
	     ajouter_liste(lO,*etud);
	   }
	 }
       }
    }  
  }
  free(tmp);
}


liste* liste_chemin_trouver(liste *l){
  l_noeud *actuel= l->premier;
  liste *listeF =malloc(sizeof(liste));
  noeud_t *nouveau = malloc(sizeof(noeud_t));
  int compteur = 0;
  while (actuel->suivant!= NULL){
    actuel = actuel->suivant;
  }
  listeF->premier = actuel;
  while (actuel->noeud.parent != NULL){
    actuel = actuel->noeud.parent;
    ajouter_debut_liste(listeF,actuel->noeud);
   }
  return listeF;
}

liste* recherche_chemin(case_t map[21][21], int departX, int departY ,int  arriveeX , int arriveeY){
  noeud_t nArrivee;
  
  liste *liste_ouverte, *liste_fermee,*liste_finalle;
  l_noeud *p_liste_ouverte,*p_liste_fermee,*nCourant;
  
  p_liste_ouverte = malloc(sizeof(l_noeud));
  p_liste_fermee = malloc(sizeof(l_noeud));
  liste_ouverte = malloc(sizeof(liste));
  liste_fermee = malloc(sizeof(liste));
  nCourant = malloc(sizeof(l_noeud));
  nArrivee.x = arriveeX;
  nArrivee.y = arriveeY;
  
  nCourant->noeud.x = departX;
  nCourant->noeud.y = departY;
  nCourant->noeud.cout_g = 0;
  nCourant->noeud.cout_h = distance_noeud(nCourant->noeud,nArrivee);
  nCourant->noeud.cout_f = nCourant->noeud.cout_g+nCourant->noeud.cout_h;
  nCourant->noeud.parent = NULL;
  
  p_liste_ouverte->noeud = nCourant->noeud;
  p_liste_ouverte->suivant = NULL;
  
  p_liste_fermee->noeud = nCourant->noeud;
  p_liste_fermee->suivant = NULL;
  
  liste_ouverte->premier = p_liste_ouverte;
  liste_fermee->premier = p_liste_fermee;
  
  ajouter_cases_adj(liste_fermee,liste_ouverte,map,nCourant,nArrivee);
  while (!((nCourant->noeud.x == arriveeX) && (nCourant->noeud.y == arriveeY))  && liste_ouverte->premier != NULL && nCourant->noeud.x <21 &&  nCourant->noeud.y < 21){

    //récupere le meilleur noeud de la liste ouverte
    nCourant = meilleur_noeud(liste_ouverte);
    
    //ajoute le meilleur noeuds à la liste fermer
    ajouter_liste(liste_fermee,nCourant->noeud);  
    
    //ajoute les noeuds adjacents dans la liste ouverte si ils sont utilisable
    ajouter_cases_adj(liste_fermee,liste_ouverte,map,nCourant,nArrivee);
    
    //supprimer le noeud de la liste ouverte car il n'est plus explorable
    supprimer(liste_ouverte,nCourant->noeud);
    
  }
  
  liste_finalle = liste_chemin_trouver(liste_fermee);

free(nCourant);
free(p_liste_ouverte);
free(p_liste_fermee);
free(liste_ouverte);
free(liste_fermee);

return liste_finalle;
}


