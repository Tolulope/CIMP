#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
 * refpixel : pixel de référence
 * comppixel : pixel à comparer
 * tolerance : seuil de tolérance de la comparaison
 *
 * retourne true si les composantes rouge, vert, bleu du pixel à comparer ont chacune
 * une différence en-dessous du seuil de tolérance, avec le pixel de référence
 * */
bool is_under_threshold(SDL_Color refpixel, SDL_Color comppixel, Uint8 tolerance) {
    return abs(refpixel.r - comppixel.r) <= tolerance
    && abs(refpixel.g - comppixel.g) <= tolerance
    && abs(refpixel.b - comppixel.b) <= tolerance;
}



 SDL_Surface *selection_color(SDL_Color *color, Uint8 tolerance, SDL_Surface *imagedata,SDL_Renderer *renderer, SDL_Texture *texture, int posx, int posy){

    Uint32* refimg = (Uint32*) imagedata->pixels;
     Uint32 max_index = (imagedata->w * imagedata->h) - 1;
     /*** CHOIX ***/

     Uint32 color_selection_border = SDL_MapRGB(imagedata->format, color->r, color->g, color->b);
     SDL_Surface* surf_tmp = SDL_CreateRGBSurfaceWithFormat(0, imagedata->w, imagedata->h, 32, imagedata->format->format);
            SDL_Color color1 = {.r=0,.g=0,.b=0};
            SDL_GetRGB(refimg[posy * imagedata->w + posx], imagedata->format, &color1.r, &color1.g, &color1.b);

            SDL_BlitSurface(imagedata, NULL, surf_tmp, NULL);
            Uint32* pixels = surf_tmp->pixels;
            SDL_LockSurface(surf_tmp);
             for (Uint32 current_index = 0; current_index < max_index; current_index++) {
                 SDL_Color current_pixel;
                 SDL_GetRGB(refimg[current_index], imagedata->format, &current_pixel.r, &current_pixel.g, &current_pixel.b);

                 if (is_under_threshold(color1, current_pixel, tolerance))
                     pixels[current_index] = color_selection_border;
             }
            SDL_UnlockSurface(surf_tmp);
           SDL_Texture *texture_selection = SDL_CreateTextureFromSurface(renderer, surf_tmp);

            //SDL_RenderCopy(renderer, texture_selection, NULL, NULL);

           SDL_Surface *surfaceSelection = SDL_CreateRGBSurfaceWithFormat(0, imagedata->w, imagedata->h, 32, imagedata->format->format);
            SDL_BlitSurface(surf_tmp, NULL, surfaceSelection, NULL);

            return surfaceSelection;

 }



void remplissage_all(SDL_Surface *surface, SDL_Texture *texture, Uint8 R, Uint8 G,Uint8 B){

 SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format , R, G, B));

 SDL_UpdateTexture(texture, NULL, surface->pixels, surface->w * sizeof(Uint32));


}


void remplissage_selection(SDL_Surface *surface,SDL_Texture *texture, Uint8 R, Uint8 G,Uint8 B,int x,int y,int w,int h){

SDL_Rect rect={x,y,w,h};
SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format , R, G,B));
SDL_UpdateTexture(texture, NULL, surface->pixels, surface->w * sizeof(Uint32));

}


void gris(SDL_Surface *image, SDL_Texture *texture){


 Uint32 * pixels = (Uint32 *)image->pixels;

 for (int y = 0; y < image->h; y++)
                    {
                        for (int x = 0; x < image->w; x++)
                        {
                            Uint32 pixel = pixels[y * image->w + x];

                            Uint8 r = pixel >> 16 & 0xFF;
                            Uint8 g = pixel >> 8 & 0xFF;
                            Uint8 b = pixel & 0xFF;

                            Uint8 v = (r + g + b) / 3;

                            pixel = (0xFF << 24) | (v << 16) | (v << 8) | v;
                            pixels[y * image->w + x] = pixel;
                        }
                    }
SDL_UpdateTexture(texture, NULL, image->pixels, image->w * sizeof(Uint32));



}

void gris_selection(SDL_Surface *image, SDL_Texture *texture,int x,int y,int w,int h){


     Uint32 * pixels = (Uint32 *)image->pixels;
 for(int i = y; i < h+y ; i++){
    for(int j = x; j < w+x; j++)
    {

                        Uint32 pixel = pixels[i * image->w + j];

                            Uint8 r = pixel >> 16 & 0xFF;
                            Uint8 g = pixel >> 8 & 0xFF;
                            Uint8 b = pixel & 0xFF;

                            Uint8 v = (r + g + b) / 3;

                            pixel = (0xFF << 24) | (v << 16) | (v << 8) | v;
                            pixels[i * image->w + j] = pixel;
                        }
                    }
SDL_UpdateTexture(texture, NULL, image->pixels, image->w * sizeof(Uint32));



}



void negatif(SDL_Surface *image, SDL_Texture *texture){



     Uint32 * pixels = (Uint32 *)image->pixels;
     for (int y = 0; y < image->h; y++)
                {
                    for (int x = 0; x < image->w; x++)
                    {
                        Uint32 pixel = pixels[y * image->w + x];
                        Uint8 r = pixel >> 16 & 0xFF;
                        Uint8 g = pixel >> 8 & 0xFF;
                        Uint8 b = pixel & 0xFF;
                        r = 255 - r;
                        g = 255 - g;
                        b = 255 - b;
                        pixel = (0xFF << 24) | (r << 16) | (g << 8) | b;
                        pixels[y * image->w + x] = pixel;
                    }
                }
SDL_UpdateTexture(texture, NULL, image->pixels, image->w * sizeof(Uint32));

}

void negatif_selection(SDL_Surface *image, SDL_Texture *texture, int x,int y,int w,int h){


Uint32 * pixels = (Uint32 *)image->pixels;
for(int i = y; i < h+y ; i++){
    for(int j = x; j < w+x; j++)
    {
                        Uint32 pixel = pixels[i * image->w + j];
                        Uint8 r = pixel >> 16 & 0xFF;
                        Uint8 g = pixel >> 8 & 0xFF;
                        Uint8 b = pixel & 0xFF;
                        r = 255 - r;
                        g = 255 - g;
                        b = 255 - b;
                        pixel = (0xFF << 24) | (r << 16) | (g << 8) | b;
                        pixels[i * image->w + j] = pixel;
                    }
                }
SDL_UpdateTexture(texture, NULL, image->pixels, image->w * sizeof(Uint32));

}


Uint8 fonction_luminosite(Uint8 c, int n)
{
    if(c + n > 255)
        return 255;
    else if(c + n < 0)
        return 0;
    else
        return c + n;
}

Uint8 fonction_contraste(Uint8 c, double n)
{
    if(c <= 255 / 2)
        return (Uint8)( (255/2) * SDL_pow((double) 2 * c / 255, n));
    else
        return 255 - fonction_contraste(255 - c, n);
}


void luminosite(SDL_Surface *image, SDL_Texture *texture,int n){

Uint32 * pixels = (Uint32 *)image->pixels;
    SDL_Color color;
    //int n=80;
 for(int i = 0; i < image->h; i++){
    for(int j = 0; j < image->w; j++)
    {
        SDL_GetRGB(pixels[i * image->w + j], image->format, &color.r, &color.g, &color.b);
        color.r = fonction_luminosite(color.r, n);
        color.g = fonction_luminosite(color.g, n);
        color.b = fonction_luminosite(color.b, n);
        pixels[i * image->w + j] = SDL_MapRGB(image->format, color.r, color.g, color.b);
    }
}
    SDL_UpdateTexture(texture, NULL, image->pixels, image->w * sizeof(Uint32));


}

void luminosite_selection(SDL_Surface *image, SDL_Texture *texture,int n,int x,int y,int w,int h){

Uint32 * pixels = (Uint32 *)image->pixels;
    SDL_Color color;
    //int n=80;
    for(int i = y; i < h+y ; i++){
    for(int j = x; j < w+x; j++)
    {
        SDL_GetRGB(pixels[i * image->w + j], image->format, &color.r, &color.g, &color.b);
        color.r = fonction_luminosite(color.r, n);
        color.g = fonction_luminosite(color.g, n);
        color.b = fonction_luminosite(color.b, n);
        pixels[i * image->w + j] = SDL_MapRGB(image->format, color.r, color.g, color.b);
    }
}
    SDL_UpdateTexture(texture, NULL, image->pixels, image->w * sizeof(Uint32));


}

void contraste(SDL_Surface *image, SDL_Texture *texture,int n){

    Uint32 * pixels = (Uint32 *)image->pixels;
    SDL_Color color;
    //int n=5;
    for(int i = 0; i < image->h; i++){
    for(int j = 0; j < image->w; j++)
    {
        SDL_GetRGB(pixels[i * image->w + j], image->format, &color.r, &color.g, &color.b);
        color.r = fonction_contraste(color.r, n);
        color.g = fonction_contraste(color.g, n);
        color.b = fonction_contraste(color.b, n);
        pixels[i * image->w + j] = SDL_MapRGB(image->format, color.r, color.g, color.b);
    }
}
    SDL_UpdateTexture(texture, NULL, image->pixels, image->w * sizeof(Uint32));


}


