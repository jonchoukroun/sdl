#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "l_texture.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int init_sdl();
int init_sdl_img();

int init_window(SDL_Window **, char *);
int init_renderer(SDL_Window **, SDL_Renderer **);
void close_sdl(SDL_Window **, SDL_Renderer **, LTexture *, LTexture *);

int load_media(SDL_Renderer **, LTexture *, LTexture *);

