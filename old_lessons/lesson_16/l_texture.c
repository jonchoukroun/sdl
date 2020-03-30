#include "l_texture.h"

void initialize(LTexture *texture)
{
  texture->m_texture = NULL;
  texture->m_width = 0;
  texture->m_height = 0;
}

void destroy(LTexture *texture)
{
  free_texture(texture);
}

int load_from_rendered_text(SDL_Renderer **renderer, LTexture *texture, TTF_Font **font, SDL_Color text_color, char *text)
{
  free_texture(texture);

  SDL_Surface *text_surface = TTF_RenderText_Solid(*font, text, text_color);
  if (text_surface == NULL) {
    printf("Failed to render text surface. SDL_ttf error: %s\n", TTF_GetError());
    return 0;
  }

  SDL_Texture *new_texture = NULL;
  new_texture = SDL_CreateTextureFromSurface(*renderer, text_surface);
  if (new_texture == NULL) {
    printf("Failed to create texture from rendered text. SDL error: %s\n", SDL_GetError());
    return 0;
  }

  texture->m_width = text_surface->w;
  texture->m_width = text_surface->h;

  SDL_FreeSurface(text_surface);

  texture->m_texture = new_texture;

  return new_texture != NULL;
}

void free_texture(LTexture *texture)
{
  if (texture && texture->m_texture) {
    SDL_DestroyTexture(texture->m_texture);
    initialize(texture);
  }
}

void render(SDL_Renderer **renderer, LTexture *texture)
{
  SDL_RenderCopy(*renderer, texture->m_texture, NULL, NULL);
}

int get_width(LTexture *texture)
{
  return texture->m_width;
}

int get_height(LTexture *texture)
{
  return texture->m_height;
}
