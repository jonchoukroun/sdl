#include "l_texture.h"

void init_texture(LTexture *texture)
{
  texture->m_texture = NULL;
  texture->m_width = 0;
  texture->m_height = 0;
}

void destroy(LTexture *texture)
{
  free_texture(texture);
}

int load_from_rendered_text(SDL_Renderer **renderer, LTexture *texture, TTF_Font **font, SDL_Color color, char *text)
{
  free_texture(texture);

  SDL_Surface *text_surface = TTF_RenderText_Solid(*font, text, color);
  if (text_surface == NULL) {
    printf("Failed to render text surface. Error: %s\n", TTF_GetError());
    return 0;
  }

  SDL_Texture *new_texture = NULL;
  new_texture = SDL_CreateTextureFromSurface(*renderer, text_surface);
  if (new_texture == NULL) {
    printf("Failed to create texture from text surface. Error: %s\n", SDL_GetError());
    return 0;
  }

  texture->m_height = text_surface->h;
  texture->m_width = text_surface->w;

  SDL_FreeSurface(text_surface);

  texture->m_texture = new_texture;

  return new_texture != NULL;
}

void free_texture(LTexture *texture)
{
  if (texture && texture->m_texture) {
    SDL_DestroyTexture(texture->m_texture);
    init_texture(texture);
  }
}

void render_texture(SDL_Renderer **renderer, LTexture *texture, int x, int y, SDL_Rect *clip)
{
  SDL_Rect render_quad = { x, y, texture->m_width, texture->m_height };

  if (clip != NULL) {
    render_quad.w = clip->w;
    render_quad.h = clip->h;
  }

  SDL_RenderCopy(*renderer, texture->m_texture, clip, &render_quad);
}

int get_width(LTexture *texture)
{
  return texture->m_width;
}

int get_height(LTexture *texture)
{
  return texture->m_height;
}
