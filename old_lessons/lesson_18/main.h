#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "l_texture.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

enum KeyPressSurface {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
} KeyPressSurface;

int init_sdl();
int init_sdl_img();

int init_window(SDL_Window **, char *);
int init_renderer(SDL_Window **, SDL_Renderer **);
int create_surface(SDL_Window **, SDL_Surface **);

int load_media(SDL_Renderer **renderer, LTexture *[]);

void close_renderer(SDL_Window **, SDL_Renderer **, LTexture *[]);
