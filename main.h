#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "l_texture.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

enum SFX_WAVS {
  SCRATCH_SFX,
  HIGH_SFX,
  MEDIUM_SFX,
  LOW_SFX,
  TOTAL_SFX
} SFX_WAVS;

int init_sdl();
int init_sdl_img();
int init_sdl_mixer();

int init_window(SDL_Window **, char *);
int init_renderer(SDL_Window **, SDL_Renderer **);

int load_image(SDL_Renderer **renderer, LTexture *);
int load_audio(Mix_Music **, Mix_Chunk *[]);

void close_audio(Mix_Music **, Mix_Chunk *[]);
void close_renderer(SDL_Window **, SDL_Renderer **, LTexture *);
