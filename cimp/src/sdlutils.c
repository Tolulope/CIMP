#include "sdlutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "transformations/trans_couleurs.h"
#include "cli/cmdprocessing.h"
#include "cli/cmdargs.h"
#include "load_save/save.h"
#include "transformations/modification.h"
#define NB_SURFACES 3


SDL_Surface** init_image_data() {
    SDL_Surface** imagedata = calloc(NB_SURFACES, sizeof(*imagedata));
    return imagedata;
}


void view_one(SDL_Surface * imagedata){

     SDL_Window *window;
     SDL_Renderer *renderer;
     SDL_Texture *texture;

     window = SDL_CreateWindow("cimp",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  imagedata->w, imagedata->h, 0);
     renderer = SDL_CreateRenderer(window, -1, 0);
     texture= SDL_CreateTextureFromSurface(renderer, imagedata);



int quit=0;
SDL_Event event;
  while (!quit) {

SDL_WaitEvent(&event);
switch (event.type) {

    case SDL_QUIT:
                quit = 1;
                break;


    }

     SDL_RenderPresent(renderer);
     SDL_RenderCopy(renderer, texture, NULL, NULL);




}
SDL_DestroyWindow(window);


}


void view_all(SDL_Surface * imagedata[]){


//S'il n'y a pas d'image

   SDL_Window *window[2];
   SDL_Renderer *renderer[2];
   SDL_Texture *texture[2];

   //S'il n'y a pas d'image

   if(imagedata[0]==NULL){
    window[0] = SDL_CreateWindow("cimp",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  800, 600, 0);


   }
   if(imagedata[1]==NULL){
    window[1] = SDL_CreateWindow("cimp",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  800, 600, 0);


   }
    if(imagedata[2]==NULL){
    window[2] = SDL_CreateWindow("cimp",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  800, 600, 0);


   }
if(imagedata[0]!=NULL){
       window[0] = SDL_CreateWindow("cimp",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  imagedata[0]->w, imagedata[0]->h, 0);
       renderer[0] = SDL_CreateRenderer(window[0], -1, 0);

       texture[0]= SDL_CreateTextureFromSurface(renderer[0], imagedata[0]);
    }


    if(imagedata[1]!=NULL){
      window[1]  = SDL_CreateWindow("cimp",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  imagedata[1]->w, imagedata[1]->h, 0);
      renderer[1] = SDL_CreateRenderer(window[1], -1, 0);
      texture[1]= SDL_CreateTextureFromSurface(renderer[1], imagedata[1]);
    }
    if(imagedata[2]!=NULL){
      window[2]  = SDL_CreateWindow("cimp",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  imagedata[2]->w, imagedata[2]->h, 0);
      renderer[2] = SDL_CreateRenderer(window[2], -1, 0);
      texture[2]= SDL_CreateTextureFromSurface(renderer[2], imagedata[2]);

    }



 int quit=0;
SDL_Event event;
  while (!quit) {

SDL_WaitEvent(&event);
switch (event.type) {

    case SDL_QUIT:
                quit = 1;
                break;
    case SDL_WINDOWEVENT:

        switch (event.window.event) {
        case SDL_WINDOWEVENT_CLOSE:
            SDL_Log("ferme %d",event.window.windowID);
            SDL_DestroyWindow(SDL_GetWindowFromID(event.window.windowID));

            break;

        }

        break;



    }
if(imagedata[0]!=NULL){
     SDL_RenderPresent(renderer[0]);
     SDL_RenderCopy(renderer[0], texture[0], NULL, NULL);
}
if(imagedata[1]!=NULL){
     SDL_RenderPresent(renderer[1]);
     SDL_RenderCopy(renderer[1], texture[1], NULL, NULL);
}
if(imagedata[2]!=NULL){
   SDL_RenderPresent(renderer[2]);
    SDL_RenderCopy(renderer[2], texture[2], NULL, NULL);
}


}


}

/** fonction pour editer l'image **/

void edit_image(SDL_Surface *imagedata, SDL_Surface *originalPic,SDL_Texture * texture) {

/****** creation du thread  *********/
int   threadReturnValue;
SDL_Thread *thread=SDL_CreateThread(edit_command,"test",NULL );

 //pthread_create(&structure.tid, NULL, threadFunction, (void*)0);


 //   pthread_join(structure.tid, NULL) ;
	// SDL_Surface *imagedata = IMG_Load(img);
//	imagedata = SDL_ConvertSurfaceFormat(imagedata, SDL_PIXELFORMAT_ARGB8888, 0);


    //S'il n'y a pas d'image
    if (imagedata == NULL) {
        return;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2 fenetre",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  imagedata->w, imagedata->h, 0);

   SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
   // SDL_Surface *originalPic=SDL_CreateRGBSurface(imagedata->flags, imagedata->w, imagedata->h, imagedata->format->BitsPerPixel, imagedata->format->Rmask, imagedata->format->Gmask, imagedata->format->Bmask, imagedata->format->Amask);
    SDL_Surface *newSurface=imagedata;
  //  SDL_BlitSurface(imagedata, NULL,originalPic,NULL);

   // for (int i = 0; imagedata[i] != NULL; i++) {
         texture = SDL_CreateTextureFromSurface(renderer, imagedata);
       // SDL_RenderCopy(renderer,  structure.texture , NULL, NULL);
  //  }

 //   SDL_RenderPresent(renderer);
    int quit = 0;
    int res=1;
    int res2=1;

    /** rectangles pour la selection **/
	SDL_Rect rectangle;
    SDL_Rect rectangle2;
      int i=0;
   int x=0;
   int y=0;
   int h=0;
   int w=0;

   int x2=0;
   int y2=0;
   int h2=0;
   int w2=0;
	bool leftMouseButtonDown;
    Uint32 * pixels = (Uint32 *)imagedata->pixels;

    /*** Parametres pour une deuxieme fenetre (recadrage)****/
    SDL_Surface *surf =NULL;
    SDL_Window *second_window=NULL;
    SDL_Renderer   *second_renderer=NULL;
    SDL_Texture    *second_texture=NULL;

      SDL_Window  *window_copier=NULL;
     SDL_Renderer   *renderer_copier=NULL;
    SDL_Texture   * texture_copier=NULL;
  SDL_Surface *newSurf=NULL;

SDL_Surface *surfaceBefore;
SDL_Surface *surfaceSelect;
surfaceSelect = SDL_CreateRGBSurface(imagedata->flags, imagedata->w, imagedata->h, imagedata->format->BitsPerPixel, imagedata->format->Rmask, imagedata->format->Gmask, imagedata->format->Bmask, imagedata->format->Amask);

int posx, posy;
    while (!quit) {
       //      SDL_UpdateTexture(strcture.texture, NULL, imagedata[0]->pixels, imagedata[0]->w * sizeof(Uint32));
		SDL_WaitEvent(&structure.event);

	if(commande!=27){
        SDL_BlitSurface(imagedata, NULL,surfaceSelect,NULL);
	}
    switch (structure.event.type) {

    case SDL_WINDOWEVENT:

        switch (structure.event.window.event) {
            case SDL_WINDOWEVENT_CLOSE:
            quit = 1;
            commande=101;
            printf("taper 'exit edit' pour quitter le mode edit\n");
            SDL_DestroyWindow(SDL_GetWindowFromID(structure.event.window.windowID));

            break;
        }


        /**if (structure.event.window.event == SDL_WINDOWEVENT_ENTER) {
				leftMouseButtonDown = false;
			}**/
            break;

           case SDL_MOUSEMOTION:

            if (leftMouseButtonDown && (commandeSelection==11 || commande==19)) {
                //int x, y;
                //SDL_GetMouseState(&x, &y);

                rectangle.w = structure.event.motion.x - rectangle.x;
                rectangle.h = structure.event.motion.y - rectangle.y;
                res=SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                SDL_RenderDrawRect(renderer, &rectangle);
                x=rectangle.x;
                y=rectangle.y;
                h=rectangle.h;
                w=rectangle.w;

            }
              if (leftMouseButtonDown) {
                //int x, y;
                //SDL_GetMouseState(&x, &y);

                rectangle2.w = structure.event.motion.x - rectangle2.x;
                rectangle2.h = structure.event.motion.y - rectangle2.y;
                if(commande==20){
                res=SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                SDL_RenderDrawRect(renderer, &rectangle2);
                }
                /** selectionner dans une autre image **/
                if(commande==31){
                res2=SDL_SetRenderDrawColor(renderer_copier, 255, 0, 0, 0);
                SDL_RenderDrawRect(renderer_copier, &rectangle2);
                }
                x2=rectangle2.x;
                y2=rectangle2.y;
                h2=rectangle2.h;
                w2=rectangle2.w;

            }


            break;
case SDL_MOUSEBUTTONUP:
            leftMouseButtonDown = false;
			break;

            case SDL_MOUSEBUTTONDOWN:
            leftMouseButtonDown = true;
            switch( structure.event.button.button )
{

case SDL_BUTTON_RIGHT:
    printf("dddddd");
SDL_BlitSurface(surfaceSelect, NULL,imagedata,NULL);
SDL_UpdateTexture(texture, NULL, surfaceSelect->pixels, surfaceSelect
                  ->w * sizeof(Uint32));

break;
case SDL_BUTTON_LEFT:
if(commande==27){

     /**       while(i<1){
            surfaceBefore = SDL_CreateRGBSurface(imagedata->flags, imagedata->w, imagedata->h, imagedata->format->BitsPerPixel, imagedata->format->Rmask, imagedata->format->Gmask, imagedata->format->Bmask, imagedata->format->Amask);
            SDL_BlitSurface(imagedata, NULL,surfaceBefore,NULL);
            i++;
   }**/
   printf("%d",i);

            SDL_GetMouseState(&posx, &posy);
            SDL_Color color = {R1,G1,B1,0};
surfaceBefore=selection_color(&color, threshold, imagedata,renderer,texture,posx, posy);
SDL_BlitSurface(surfaceBefore, NULL,imagedata,NULL);
SDL_UpdateTexture(texture, NULL, surfaceBefore->pixels, surfaceBefore->w * sizeof(Uint32));

               }
               break;


}





 if(commandeSelection==11 || commande==19){

 SDL_GetMouseState(&rectangle.x, &rectangle.y);


  }

  if(commande==20 || commande==31){

 SDL_GetMouseState(&rectangle2.x, &rectangle2.y);

}
   if(commande==1){
                   rectangle.x=40;
   rectangle.y=40;
   rectangle.h=200;
   rectangle.w=200;
SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
SDL_RenderDrawRect(renderer, &rectangle);


 }

			    break;



}

if(res==0){



        if(commande==19 || commandeSelection==11){

             SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            SDL_RenderDrawRect(renderer, &rectangle);

        }


        if(commande==20){

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            SDL_RenderDrawRect(renderer, &rectangle2);

        }


 //SDL_RenderFillRect(renderer,&rectangle);
 //SDL_UpdateTexture(structure.texture, NULL, imagedata[0]->pixels, imagedata[0]->w * sizeof(Uint32));


}

 if(commande==31 && res2==0){

            SDL_SetRenderDrawColor(renderer_copier, 255, 0, 0, 0);
            SDL_RenderDrawRect(renderer_copier, &rectangle2);

        }

if(commande==18){

    rectangle.x=0;
    rectangle.y=0;
    rectangle.w=0;
    rectangle.h=0;

    rectangle2.x=0;
    rectangle2.y=0;
    rectangle2.w=0;
    rectangle2.h=0;
//SDL_RenderDrawRect(renderer, &rectangle);

 //SDL_RenderFillRect(renderer,&rectangle);
 //SDL_UpdateTexture(structure.texture, NULL, imagedata[0]->pixels, imagedata[0]->w * sizeof(Uint32));

commande=0;
commandeSelection=0;

}


/** copier une partie de l'image dans la meme fenetre **/
if(commande==21){

printf("bjr\n");
printf("%d\n",x);
printf("%d\n",x2);

copier(imagedata, imagedata, texture,x, y, w, h, x2, y2);
// count==0;
commande=0;
}


/** couper une partie de l'image dans la meme fenetre **/

if(commande==28){

printf("bjr\n");
printf("%d\n",x);
printf("%d\n",x2);

couper(imagedata, imagedata, texture,NULL, x,y,w,h, x2, y2);
commande=0;
}


/** copier une partie de l'image dans une autre fenetre **/
if(commande==32){

copier(imagedata, structure.imagedata[1],texture_copier,x, y, w, h, x2, y2);
commande=0;
}

/** couper une partie de l'image dans une autre fenetre **/
if(commande==33){

couper(imagedata, structure.imagedata[1],texture,texture_copier,x, y, w, h, x2, y2);
commande=0;
}


if(commande==34){
    SDL_Rect rect = {0, 0, 32, 32}; // the rect is where you wants the texture to be drawn (screen coordinate).
    SDL_Rect crop = {0, 0, 16, 16}; // the crop is what part of the image we want to display.

    float angle = 180.0f; // set the angle.
    SDL_Point center = {8, 8}; // the center where the texture will be rotated.
    SDL_RendererFlip flip = SDL_FLIP_NONE; // the flip of the texture.

    // now, try to draw something
    SDL_RenderCopyEx(renderer, texture, &crop , &rect, angle, &center, flip);
SDL_UpdateTexture(texture, NULL, imagedata->pixels, imagedata->w * sizeof(Uint32));

commande=0;
}


/*** Recadrage rectangulaire ***/

if(res==0 && commande==13){

        structure.secondSurface = coupe_surf(imagedata,x,y,w, h);
        second_window = SDL_CreateWindow("recadrage",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, structure.secondSurface->w,  structure.secondSurface->h, 0);
        second_renderer = SDL_CreateRenderer(second_window, -1, SDL_RENDERER_ACCELERATED);
        second_texture = SDL_CreateTextureFromSurface(second_renderer, structure.secondSurface );
               // SDL_UpdateTexture(magnified_fragment_texture, NULL, imagedata[0]->pixels, imagedata[0]->w * sizeof(Uint32));
   commande=0;
               }


               if(commande==29){


        window_copier = SDL_CreateWindow("image2",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  structure.imagedata[1]->w,  structure.imagedata[1]->h, 0);
        renderer_copier = SDL_CreateRenderer(window_copier, -1, SDL_RENDERER_ACCELERATED);
        texture_copier = SDL_CreateTextureFromSurface(renderer_copier, structure.imagedata[1] );

      copier(structure.imagedata[1], structure.imagedata[1],texture_copier , x, y, w, h, x2, y2);
        commande=0;
               }

/** remplissage d'une selection **/

if(res==0 && commande==10 && commandeSelection==11){


R1 =(Uint8) R;
G1 =(Uint8) G;
B1 =(Uint8) B;
remplissage_selection(imagedata,texture,R1,G1,B1, x,y,w,h);
commande=0;

}


/*** Remplissage à revoir ***/
if(commande==4){



R1 =(Uint8) R;
G1 =(Uint8) G;
B1 =(Uint8) B;

remplissage_all(imagedata, texture, R1, G1, B1);
// remplissage_all(imagedata, texture, color);
  commande=0;

}

/** negatif **/
if(commande==5){

negatif(imagedata, texture);

commande=0;

}



if(commande==16){

negatif_selection(imagedata, texture,x,y,w,h);
  commande=0;
}
/** luminosite **/

if(commande==6){

luminosite_selection(imagedata,texture,valeurN,x,y,w,h);
commande=0;
}


if(commande==7){
printf("%d",valeurN);
luminosite(imagedata,texture,valeurN);
commande=0;
}

/** contraste **/
if(commande==8){

contraste(imagedata,texture,valeurN );
commande=0;
}

/** gris **/
if(commande==12){

gris(imagedata,texture);
//SDL_BlitSurface(original, NULL,imagedata[0],NULL);
//SDL_UpdateTexture(structure.texture, NULL, original->pixels, original->w * sizeof(Uint32));
   commande=0;
}

/** gris selection **/
if(commande==17 && commandeSelection==11){

    gris_selection(imagedata,texture,x,y,w,h);

}

/** annuler toutes les modifications **/
if(commande==22){

SDL_BlitSurface(originalPic, NULL,imagedata,NULL);
SDL_UpdateTexture(texture, NULL, originalPic->pixels, originalPic->w * sizeof(Uint32));

commande=0;

}

if(commande==23){
SDL_Rect dest;
dest.x = 0;
dest.y = 0;
dest.w = 800;
dest.h = 600;
SDL_Surface *resize=SDL_CreateRGBSurface(imagedata->flags,  imagedata->w, imagedata->h, imagedata->format->BitsPerPixel, imagedata->format->Rmask, imagedata->format->Gmask, imagedata->format->Bmask, imagedata->format->Amask);
SDL_BlitScaled(resize, NULL,imagedata,&dest);
SDL_UpdateTexture(texture, NULL, resize->pixels, resize->w * sizeof(Uint32));

commande=0;

}


/** symetrie horizontale **/
if(commande==24){
//horizontale
symetrie(imagedata, "horizontale",texture);

commande=0;


}

/** symetrie verticale **/
if(commande==25){
//verticale
symetrie(imagedata, "verticale",texture);
commande=0;

}


/** ajout d'une marge autour de l'image selectionné **/
if(commande==26){


add_marge(imagedata,texture,x,y,w,h);

commande=0;

}





/** femer la deuxieme fenetre **/

if(commande==14){

SDL_DestroyTexture(second_texture);
SDL_DestroyRenderer(second_renderer);
SDL_DestroyWindow(second_window);

}

/** sauvegarde test a revoir
if(commande==123){

      IMG_SaveJPG(imagedata[0], "out_0420.jpg",100);
 }
**/


        SDL_RenderPresent(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);

		/** deuxieme fenetre **/
  if(second_renderer) {
         SDL_Rect srcrect = {600, 500, 250, 250};
            const SDL_Rect dstrect = {0, 0, srcrect.w*2, srcrect.h*2};


            // RenderCopy scales texture to destination rect
            SDL_RenderCopy(second_renderer, second_texture, NULL, NULL);
            SDL_RenderPresent(second_renderer);
        }
  if(renderer_copier) {
            SDL_RenderPresent(renderer_copier);
            SDL_RenderCopy(renderer_copier, texture_copier, NULL, NULL);

        }
		}

/** test
if(commande==126){

 SDL_Window *window2 = SDL_CreateWindow("SDL2 fenetre",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
 SDL_Surface *screenSurface = SDL_GetWindowSurface( window2 );
   SDL_Renderer * renderer2 = SDL_CreateRenderer(window2, -1, 0);
     SDL_CreateTextureFromSurface(renderer2, screenSurface);


} **/


//SDL_DestroyTexture(texture);
//free(texture);

SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);

/**
if(commande==101){

SDL_FreeSurface(imagedata[0]);
free(structure.imagedata);

}**/

 /** Attente jusqu'à la fin du thread ***/

//pthread_cancel(structure.tid);

SDL_WaitThread(thread,&threadReturnValue);

}

void free_image_data(SDL_Surface** image_data) {
    for (int i = 0; i < NB_SURFACES; i++) {
        SDL_FreeSurface(image_data[i]);
    }
    free(image_data);
	IMG_Quit();
	SDL_Quit();
}
