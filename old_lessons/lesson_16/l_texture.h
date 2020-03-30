#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

typedef struct LTexture {
  SDL_Texture *m_texture;
  int m_width;
  int m_height;
} LTexture;

void initialize(LTexture *);

int load_from_rendered_text(SDL_Renderer **, LTexture *, TTF_Font **, SDL_Color, char * text);

void free_texture(LTexture *);

void render(SDL_Renderer **, LTexture *);

int get_width(LTexture *);

int get_height(LTexture *);
