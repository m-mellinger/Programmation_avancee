#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "Affichage.h"

int nb_ligne(world_t *world){
  
  SDL_RWops* fichier = SDL_RWFromFile(world->fichier,"r");
  int taille_fichier = 0, nb_ligne = 0;
  char caractere;
  
  taille_fichier = SDL_RWseek(fichier,0,RW_SEEK_END);
  SDL_RWseek(fichier,0,RW_SEEK_SET);
  
  for (int i = 0;i<taille_fichier;i++){
      SDL_RWseek(fichier,0,RW_SEEK_CUR);
      SDL_RWread(fichier,&caractere,1,1);
      if( caractere == '\n')
	nb_ligne = nb_ligne +1;
  }
  
  SDL_RWclose(fichier);
  return nb_ligne;
}

int nb_colonne(world_t *world){
  
  SDL_RWops* fichier = SDL_RWFromFile(world->fichier,"r");
  int nb_colonne = -1;
  char caractere;
  
  SDL_RWseek(fichier,0,RW_SEEK_SET);
  
  while (caractere != '\n'){
      SDL_RWseek(fichier,0,RW_SEEK_CUR);
      SDL_RWread(fichier,&caractere,1,1);
      nb_colonne = nb_colonne +1;
  }
  
  SDL_RWclose(fichier);
  return nb_colonne;
}


void deplacerHaut(world_t *world){
  SDL_RWops* fichier = SDL_RWFromFile(world->fichier,"r");
  int c = nb_colonne(world);
  char *caractere = malloc(sizeof(char));
  int lecture;
  world->positionY = world->positionY-1;
  SDL_RWseek(fichier,0,RW_SEEK_SET);
   SDL_RWseek(fichier,world->positionX*9+(c+1)*(world->positionY),RW_SEEK_CUR);
  for(int i = 20;i>=0;i = i-1){
    if (i>=1){
     for(int j = 0;j<21;j++){
       world->tab[j][i] = world->tab[j][i-1];
     }
    }
    else{
      for(int j = 0;j<21;j++){
	lecture = 0;
	SDL_RWread(fichier,caractere,9,1);
	lecture = atoi(caractere);
	world->tab[j][i] = init_case(lecture);
     }
    }
   }
  free(caractere);
  SDL_RWclose(fichier);
}

void deplacerGauche(world_t *world){
   SDL_RWops* fichier = SDL_RWFromFile(world->fichier,"r");
  int c = nb_colonne(world);
  char *caractere = malloc(sizeof(char));
  int lecture ;
  world->positionX = world->positionX-1;
  SDL_RWseek(fichier,0,RW_SEEK_SET);
  SDL_RWseek(fichier,world->positionX*9+(c+1)*(world->positionY),RW_SEEK_CUR);
  for(int i = 0;i<21;i++){
     for(int j = 20;j>=0;j = j-1){
       if (j>=1){
	 world->tab[j][i] = world->tab[j-1][i];
       }
       else{
	 lecture = 0;
	 SDL_RWread(fichier,caractere,9,1);
	 lecture = atoi(caractere);
	 world->tab[j][i] = init_case(lecture);
	 SDL_RWseek(fichier,c-8,RW_SEEK_CUR);
       }      
     }
   }
  free(caractere);
  SDL_RWclose(fichier);
}

void deplacerBas(world_t *world){
  SDL_RWops* fichier = SDL_RWFromFile(world->fichier,"r");
  int c = nb_colonne(world);
  char *caractere = malloc(sizeof(char));
  int lecture;
  world->positionY = world->positionY+1;
  SDL_RWseek(fichier,0,RW_SEEK_SET);
  SDL_RWseek(fichier,world->positionX*9 + (c+1)*(world->positionY+20),RW_SEEK_CUR);
  for(int i = 0;i<21;i++){
    if (i<20){
     for(int j = 0;j<21;j++){
       world->tab[j][i] = world->tab[j][i+1];
     }
    }
    else{
      for(int j = 0;j<21;j++){
	lecture = 0;
	SDL_RWread(fichier,caractere,9,1);
	lecture = atoi(caractere);       
	world->tab[j][i] = init_case(lecture);
      }
    }
  }
  free(caractere);
  SDL_RWclose(fichier);
}
void deplacerDroite(world_t *world){
  SDL_RWops* fichier = SDL_RWFromFile(world->fichier,"r");
  int c = nb_colonne(world);
  char *caractere = malloc(sizeof(char));
  int lecture;
  world->positionX = world->positionX+1; 
  SDL_RWseek(fichier,0,RW_SEEK_SET);
  SDL_RWseek(fichier,(world->positionX+20)*9+(c+1)*(world->positionY),RW_SEEK_CUR);
  for(int i = 0;i<21;i++){
     for(int j = 0;j<21;j++){
       if (j<20){
	 world->tab[j][i] = world->tab[j+1][i];
       }
       else{
	 lecture = 0;
	 SDL_RWread(fichier,caractere,9,1);
	 lecture = atoi(caractere);	 
	 world->tab[j][i] = init_case(lecture);
	 SDL_RWseek(fichier,c-8,RW_SEEK_CUR);
       } 
     }
  }
  free(caractere);
  SDL_RWclose(fichier);
}

case_t init_case(int x){
  case_t c;
  c.typeMonstre = x%100;
  x = x/100;
  c.monstre = x%10;
  x = x/10;
  c.typeObstacle= x%100;
  x = x/100;
  c.obstacle = x%10;
  x = x/10;
  c.background = x % 100;
  x = x/100;
  c.accessible = x%10;
  return c;
  
}
void init_tab_map(world_t *world){
  
  SDL_RWops* fichier = SDL_RWFromFile(world->fichier,"r");
  int c = nb_colonne(world);
  char *caractere = malloc(sizeof(char));
  int lecture;
  SDL_RWseek(fichier,0,RW_SEEK_SET);
  
  for(int i = 0;i<21;i++){
    for(int j = 0;j<21;j++){
       SDL_RWread(fichier,caractere,9,1);
       lecture = atoi(caractere);
       world->tab[j][i] = init_case(lecture);
     }   
     SDL_RWseek(fichier,c-188,RW_SEEK_CUR);
  }
  free(caractere);
  SDL_RWclose(fichier);
}

void deplacementAuto(world_t *world,liste *l){

  while(l->premier->suivant != NULL){

    if (l->premier->suivant->noeud.x < l->premier->noeud.x ){ 
      deplacerGauche(world);
      afficher_jeu(world);
    }
    else if (l->premier->suivant->noeud.x > l->premier->noeud.x){
      deplacerDroite(world);
      afficher_jeu(world);

      }
    else if (l->premier->suivant->noeud.y > l->premier->noeud.y){
      deplacerBas(world);
      afficher_jeu(world);
 
      }
    if (l->premier->suivant->noeud.y < l->premier->noeud.y){
      deplacerHaut(world);
      afficher_jeu(world);
    }
    
    SDL_Delay(500);
    supprimer(l,l->premier->noeud);
    }
}

void afficher_jeu(world_t *world){
  SDL_Texture *bitmapTex;
  SDL_Surface *bitmapSurface;
  SDL_Rect SrcR,DestR;

  bitmapSurface = SDL_LoadBMP("pavage.bmp");   
  bitmapTex = SDL_CreateTextureFromSurface(world->renderer, bitmapSurface);
  SDL_FreeSurface(bitmapSurface);
   for(int i = 0;i<22;i++){
    for(int j = 0;j<22;j++){
      
      SrcR.x = 32*world->tab[i][j].background;
      SrcR.y = 0;
      SrcR.w = 32; 
      SrcR.h = 32;
 
      DestR.x = SCREEN_WIDTH/21*i;
      DestR.y = PLAYSCREEN_HEIGHT/21*j;
      DestR.w = SCREEN_WIDTH/21;
      DestR.h = PLAYSCREEN_HEIGHT/21;

      SDL_RenderCopy(world->renderer, bitmapTex,&SrcR,&DestR);
    }
  }
  
  bitmapSurface = SDL_LoadBMP("personnage.bmp");
  Uint32 colorkey = SDL_MapRGB( bitmapSurface->format, 0, 255, 255 );
  SDL_SetColorKey(bitmapSurface,1,colorkey);
  
  bitmapTex = SDL_CreateTextureFromSurface(world->renderer, bitmapSurface);
  SDL_FreeSurface(bitmapSurface);
  
  SrcR.x = 0;
  SrcR.y = 0;
  SrcR.w = 900;
  SrcR.h = 1800; 
  
  DestR.x = SCREEN_WIDTH/2-20; 
  DestR.y = PLAYSCREEN_HEIGHT/2-60;
  DestR.w = SCREEN_WIDTH/21;
  DestR.h = 2*PLAYSCREEN_HEIGHT/21;
  
  SDL_RenderCopy(world->renderer, bitmapTex,&SrcR,&DestR);

  bitmapSurface = SDL_LoadBMP("vie.bmp");
  bitmapTex = SDL_CreateTextureFromSurface(world->renderer, bitmapSurface);    
  SDL_FreeSurface(bitmapSurface);
  
  SrcR.x = 0;
  SrcR.y = 0;
  SrcR.w =512;
  SrcR.h =512; 
  
  DestR.x = SCREEN_WIDTH-0.85*SCREEN_WIDTH; 
  DestR.y = PLAYSCREEN_HEIGHT+0.6*(100-world->personnage.vie);
  DestR.w = SCREEN_WIDTH-0.9*SCREEN_WIDTH;
  DestR.h = SCREEN_HEIGHT-PLAYSCREEN_HEIGHT;
  
  SDL_RenderCopy(world->renderer, bitmapTex,&SrcR,&DestR);

  bitmapSurface = SDL_LoadBMP("pixil-frame.bmp");
  bitmapTex = SDL_CreateTextureFromSurface(world->renderer, bitmapSurface);    
  SDL_FreeSurface(bitmapSurface);
  
  SrcR.x = 0;
  SrcR.y = 0;
  SrcR.w =700 ;
  SrcR.h =70; 
  
  DestR.x = 0; 
  DestR.y = PLAYSCREEN_HEIGHT;
  DestR.w = SCREEN_WIDTH;
  DestR.h = SCREEN_HEIGHT-PLAYSCREEN_HEIGHT;
  
  SDL_RenderCopy(world->renderer, bitmapTex,&SrcR,&DestR);
  
  SDL_RenderPresent(world->renderer);
}



