




extern void copier(SDL_Surface *surface1, SDL_Surface *surface2, SDL_Texture *texture,int x,int y,int w,int h,int x2,int y2);
extern void couper(SDL_Surface *surface1, SDL_Surface *surface2, SDL_Texture *texture1,SDL_Texture *texture2,int x,int y,int w,int h,int x2,int y2);
extern SDL_Surface *symetrie(SDL_Surface *source, char *modif, SDL_Texture *texture);
extern void add_marge(SDL_Surface *surface, SDL_Texture *texture, int x,int y,int w,int h);
extern SDL_Surface* coupe_surf(SDL_Surface* image, int x, int y, int width, int height);
