#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#define WINDOW_W 840
#define WINDOW_H 840

int nb_ligne(const char* nomFichier){
  
  SDL_RWops* fichier = SDL_RWFromFile(nomFichier,"r");
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

int nb_colonne(const char* nomFichier){
  
  SDL_RWops* fichier = SDL_RWFromFile(nomFichier,"r");
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

char** tab_map(const char* nomFichier){
  
  SDL_RWops* fichier = SDL_RWFromFile(nomFichier,"r");
  int taille_fichier = 0,c = nb_colonne(nomFichier),l = nb_ligne(nomFichier) ;
  char caractere;
  char** tab;
  
  tab = malloc(sizeof(c));
  for(int i = 0;i<c;i++)
    tab[i] = malloc(sizeof(l));
  
  taille_fichier = SDL_RWseek(fichier,0,RW_SEEK_END);
  SDL_RWseek(fichier,0,RW_SEEK_SET);
    
  for(int i = 0;i<l;i++){
    for(int j = 0;j<c;j++){
      SDL_RWseek(fichier,0,RW_SEEK_CUR);
      SDL_RWread(fichier,&caractere,1,1);
      if (caractere != '\n')
	tab[j][i] = caractere;
      else
	j = j-1;
     }
   }
   
   return tab;		      
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

void afficher_map(){
SDL_Window* fenetre;
  SDL_Renderer* renderer;
  SDL_Texture *bitmapTex;
  SDL_Surface *bitmapSurface;
  SDL_Rect SrcR,DestR;
  char** tab;
  
  fenetre = SDL_CreateWindow("Une fenetre SDL" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WINDOW_W , WINDOW_H , 0);
   renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   bitmapSurface = SDL_LoadBMP("pavage.bmp");   
   bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
   SDL_FreeSurface(bitmapSurface);

   tab = tab_map("Map.txt");
   for(int i = 0;i<nb_colonne("Map.txt");i++){
     for(int j = 0;j<nb_ligne("Map.txt");j++){
  
       SrcR.x = 40*conv_char_en_entier(tab[i][j]);
       SrcR.y = 40*conv_char_en_entier(tab[i][j]);
       SrcR.w = 40; 
       SrcR.h = 40;
       
       DestR.x = 40*i;
       DestR.y = 40*j;
       DestR.w = 40;
       DestR.h = 40;
	 	 
       SDL_RenderCopy(renderer, bitmapTex,&SrcR,&DestR);
     }
   }
     SDL_RenderPresent(renderer);
  SDL_Delay(10000);
}


int main(int argc, char *argv[])
{
  afficher_map();
  printf("nombre de ligne %i \n",nb_ligne("Map.txt"));
  printf("nombre de colonne %i \n",nb_colonne("Map.txt"));
   
  return 0;
}
