#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

typedef struct LTexture {
  SDL_Texture *m_texture;
  int m_width;
  int m_height;
} LTexture;

void init_texture(LTexture *);

int load_from_rendered_text(SDL_Renderer **, LTexture *, TTF_Font **, SDL_Color, char *);

int load_from_file(SDL_Renderer **, LTexture *, char *);

void free_texture(LTexture *);

void render_texture(SDL_Renderer **, LTexture *, int x, int y, SDL_Rect *);

int get_width(LTexture *);

int get_height(LTexture *);
