#ifndef SDLUTILS_H
#define SDLUTILS_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>




struct fenetre {
  SDL_Surface* imagedata[3];
  /** pour garder une référence vers l'image original **/
  SDL_Surface* originalPic[3];
  SDL_Texture * texture[3];
  SDL_Surface *secondSurface;
 // SDL_Window* window;
 // SDL_Renderer * renderer;
//  SDL_Texture * texture;
  SDL_Event event;
};
struct fenetre structure;


/* Les données d'une image (image_data) sont représentées
 * par un tableau de type SDL_Surface**
 * dont l'indice 0 correspond à l'image et
 * les indices suivants, à des surfaces sur l'image
*/

/* Initialise une image_data */
SDL_Surface** init_image_data();

/* Visualiser l'image */
void view_all(SDL_Surface * imagedata[]);
void view_one(SDL_Surface * imagedata);
void edit_image(SDL_Surface *imagedata, SDL_Surface *originalPic,SDL_Texture *texture);

/*Libère la mémoire associée à image_data*/
void free_image_data(SDL_Surface** image_data);
#endif // SDLUTILS_H
