#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "Affichage.h"

#define WINDOW_W 840
#define WINDOW_H 840

//test
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
  int taille_fichier = 0, nb_colonne = -1;
  char caractere;
  
  taille_fichier = SDL_RWseek(fichier,0,RW_SEEK_END);
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
  int taille_fichier = 0,c = nb_colonne(world),l = nb_ligne(world);
  char caractere;
  world->positionY = world->positionY-1;
  SDL_RWseek(fichier,0,RW_SEEK_SET);
   SDL_RWseek(fichier,world->positionX+(c+1)*(world->positionY),RW_SEEK_CUR);
  for(int i = 20;i>=0;i = i-1){
    if (i>=1){
     for(int j = 0;j<21;j++){
       world->tab[j][i] = world->tab[j][i-1];
     }
    }
    else{
      for(int j = 0;j<21;j++){
       SDL_RWread(fichier,&caractere,1,1);
       world->tab[j][i] = caractere;
     }
    }
   }
   SDL_RWclose(fichier);
}

void deplacerGauche(world_t *world){
   SDL_RWops* fichier = SDL_RWFromFile(world->fichier,"r");
  int taille_fichier = 0,c = nb_colonne(world),l = nb_ligne(world);
  char caractere;
  world->positionX = world->positionX-1;
  SDL_RWseek(fichier,0,RW_SEEK_SET);
  SDL_RWseek(fichier,world->positionX+(c+1)*(world->positionY),RW_SEEK_CUR);
  for(int i = 0;i<21;i++){
     for(int j = 20;j>=0;j = j-1){
       if (j>=1){
	 world->tab[j][i] = world->tab[j-1][i];
       }
       else{
	 SDL_RWread(fichier,&caractere,1,1);
	 world->tab[j][i] = caractere;
	 SDL_RWseek(fichier,c,RW_SEEK_CUR);
       }      
     }
   }
  SDL_RWclose(fichier);
}

void deplacerBas(world_t *world){
  SDL_RWops* fichier = SDL_RWFromFile(world->fichier,"r");
  int taille_fichier = 0,c = nb_colonne(world),l = nb_ligne(world);
  char caractere;
  world->positionY = world->positionY+1;
  SDL_RWseek(fichier,0,RW_SEEK_SET);
  SDL_RWseek(fichier,world->positionX + (c+1)*(world->positionY+20),RW_SEEK_CUR);
  for(int i = 0;i<21;i++){
    if (i<20){
     for(int j = 0;j<21;j++){
       world->tab[j][i] = world->tab[j][i+1];
     }
    }
    else{
      for(int j = 0;j<21;j++){
       SDL_RWread(fichier,&caractere,1,1);
       world->tab[j][i] = caractere;
     }
    }
   }
   SDL_RWclose(fichier);
}
void deplacerDroite(world_t *world){
  SDL_RWops* fichier = SDL_RWFromFile(world->fichier,"r");
  int taille_fichier = 0,c = nb_colonne(world),l = nb_ligne(world);
  char caractere;
  world->positionX = world->positionX+1; 
  SDL_RWseek(fichier,0,RW_SEEK_SET);
  SDL_RWseek(fichier,world->positionX+20+(c+1)*(world->positionY),RW_SEEK_CUR);
  for(int i = 0;i<21;i++){
     for(int j = 0;j<21;j++){
       if (j<20){
	 world->tab[j][i] = world->tab[j+1][i];
       }
       else{
	 SDL_RWread(fichier,&caractere,1,1);
	 world->tab[j][i] = caractere;
	 SDL_RWseek(fichier,c,RW_SEEK_CUR);
       } 
     }
   }
   SDL_RWclose(fichier);; 
}

void init_tab_map(world_t *world){
  
  SDL_RWops* fichier = SDL_RWFromFile(world->fichier,"r");
  int taille_fichier = 0,c = nb_colonne(world),l = nb_ligne(world);
  char caractere;
  SDL_RWseek(fichier,0,RW_SEEK_SET);
  SDL_RWseek(fichier,world->positionX + (c+1)*world->positionY,RW_SEEK_CUR);
  
  for(int i = 0;i<21;i++){
     for(int j = 0;j<21;j++){
	SDL_RWread(fichier,&caractere,1,1);
	world->tab[j][i] = caractere;  
     }
    SDL_RWseek(fichier,c-20,RW_SEEK_CUR);
   }
  SDL_RWclose(fichier);
}


int conv_char_en_entier(char s){
  int retour;
  if (s == '0')
    retour = 0;
  if (s == '1')
    retour = 1;
  if (s == '2')
    retour = 2;
  if (s == '3')
    retour = 3;
  return retour;
}

void afficher_jeu(world_t *world){
  SDL_Texture *bitmapTex;
  SDL_Surface *bitmapSurface;
  SDL_Rect SrcR,DestR,SrcR2,DestR2;

  bitmapSurface = SDL_LoadBMP("pavage.bmp");   
  bitmapTex = SDL_CreateTextureFromSurface(world->renderer, bitmapSurface);
  SDL_FreeSurface(bitmapSurface);
   for(int i = 0;i<22;i++){
    for(int j = 0;j<22;j++){
      
      SrcR.x = 32*conv_char_en_entier(world->tab[i][j]);
      SrcR.y = 0;
      SrcR.w = 32; 
      SrcR.h = 32;
      
      DestR.x = 40*i;
      DestR.y = 40*j;
      DestR.w = 40;
      DestR.h = 40;

      SDL_RenderCopy(world->renderer, bitmapTex,&SrcR,&DestR);
    }
  }
  
  bitmapSurface = SDL_LoadBMP("sprites.bmp");
  Uint32 colorkey = SDL_MapRGB( bitmapSurface->format, 0, 255, 255 );
  SDL_SetColorKey(bitmapSurface,1,colorkey);
  
  bitmapTex = SDL_CreateTextureFromSurface(world->renderer, bitmapSurface);
  SDL_FreeSurface(bitmapSurface);
  
  SrcR2.x = 0;
  SrcR2.y = 0;
  SrcR2.w = 250/3;
  SrcR2.h = 330/3; 
  
  DestR2.x = WINDOW_W/2-20; 
  DestR2.y = WINDOW_H/2-60;
  DestR2.w = 40;
  DestR2.h = 80;
  
  SDL_RenderCopy(world->renderer, bitmapTex,&SrcR2,&DestR2);
  SDL_RenderPresent(world->renderer);
}



