
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


extern  SDL_Surface *selection_color(SDL_Color *color, Uint8 tolerance, SDL_Surface *imagedata,SDL_Renderer *renderer, SDL_Texture *texture, int posx, int posy);
extern void remplissage_all(SDL_Surface *surface, SDL_Texture *texture, Uint8 R, Uint8 G,Uint8 B);
extern void remplissage_selection(SDL_Surface *surface,SDL_Texture *texture, Uint8 R, Uint8 G,Uint8 B,int x,int y,int w,int h);
extern void gris(SDL_Surface *image, SDL_Texture *texture);
extern void negatif(SDL_Surface *image, SDL_Texture *texture);
extern void luminosite(SDL_Surface *image, SDL_Texture *texture,int n);
extern Uint8 fonction_luminosite(Uint8 c, int n);
extern void contraste(SDL_Surface *image, SDL_Texture *texture,int n);
extern Uint8 fonction_contraste(Uint8 c, double n);
extern void luminosite_selection(SDL_Surface *image, SDL_Texture *texture, int n,int x,int y,int w,int h);
extern void negatif_selection(SDL_Surface *image, SDL_Texture *texture, int x,int y,int w,int h);
extern void gris_selection(SDL_Surface *image, SDL_Texture *texture, int x,int y,int w,int h);

