#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "l_texture.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WALKING_ANIMATION_FRAMES 4

int init_sdl();
int init_sdl_img();
int init_sdl_ttf();

int init_window(SDL_Window **, char *);
int init_renderer(SDL_Window **, SDL_Renderer **);
void close_sdl(SDL_Window **, SDL_Renderer **, LTexture *, TTF_Font **);

int load_media(SDL_Renderer **, TTF_Font **, LTexture *);

