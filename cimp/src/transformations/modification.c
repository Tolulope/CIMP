#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



void copier(SDL_Surface *surface1, SDL_Surface *surface2, SDL_Texture *texture,int x,int y,int w,int h,int x2,int y2){


SDL_Rect srcrect1 = { x, y, w, h };
SDL_Rect dstrect = { x2, y2, w, h };
printf("%d\n",srcrect1.w);
printf("%d",dstrect.w);

SDL_BlitSurface( surface1, &srcrect1, surface2, &dstrect );
// SDL_FillRect(imagedata[0],&srcrect1,SDL_MapRGB(imagedata[0]->format , 0 , 0 , 0 ));
 SDL_UpdateTexture(texture, NULL, surface2->pixels, surface2->w * sizeof(Uint32));

 }

void couper(SDL_Surface *surface1, SDL_Surface *surface2, SDL_Texture *texture1,SDL_Texture *texture2,int x,int y,int w,int h,int x2,int y2){
SDL_Rect srcrect1 = { x, y, w, h };
SDL_Rect dstrect = { x2, y2, w, h };
printf("%d\n",srcrect1.w);
printf("%d",dstrect.w);

SDL_BlitSurface( surface1, &srcrect1, surface2, &dstrect );
SDL_FillRect(surface1,&srcrect1,SDL_MapRGB(surface1->format , 0, 0,0));
SDL_UpdateTexture(texture1, NULL, surface1->pixels, surface1->w * sizeof(Uint32));

if(texture2!=NULL){
SDL_UpdateTexture(texture2, NULL, surface2->pixels, surface2->w * sizeof(Uint32));
}
}

SDL_Surface *symetrie(SDL_Surface *source, char *modif, SDL_Texture *texture)
{
    SDL_Surface *reverse = SDL_CreateRGBSurface(source->flags, source->w, source->h, source->format->BitsPerPixel, source->format->Rmask, source->format->Gmask, source->format->Bmask, source->format->Amask);
    Uint32 *pixels = (Uint32 *)reverse->pixels;
    Uint32 *pixelsSource = (Uint32 *)source->pixels;
    for (int x = 0, rx = reverse->w - 1; x < reverse->w; x++, rx--)
    {
        for (int y = 0, ry = reverse->h - 1; y < reverse->h; y++, ry--)
        {
            Uint32 pixel =   pixelsSource[(y * source->w) + x];


            if (strcmp(modif,"horizontale")==0){
                         pixels[(y * reverse->w) + rx] = pixel;}


            if (strcmp(modif,"verticale")==0){
                pixels[(ry * reverse->w) + x] = pixel;}
        }
    }
    SDL_BlitSurface(reverse,NULL,source,NULL);
    SDL_UpdateTexture(texture, NULL,  reverse->pixels,  reverse->w * sizeof(Uint32));
    return reverse;
}


SDL_Surface* coupe_surf(SDL_Surface* image, int x, int y, int width, int height)

{
    SDL_Surface* surface = SDL_CreateRGBSurface(image->flags, width, height, image->format->BitsPerPixel, image->format->Rmask, image->format->Gmask, image->format->Bmask, image->format->Amask);
    SDL_Rect rect = {x, y, width, height};
    SDL_BlitSurface(image, &rect, surface, 0);

    return surface;

}



void add_marge(SDL_Surface *surface, SDL_Texture *texture, int x,int y,int w,int h){

SDL_Surface *selection =coupe_surf(surface, x,y,w,h);

SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));

SDL_Rect destination={x,y,w,h};

SDL_BlitSurface(selection,NULL,surface,&destination);
SDL_UpdateTexture(texture, NULL,  surface->pixels, surface->w * sizeof(Uint32));


}


