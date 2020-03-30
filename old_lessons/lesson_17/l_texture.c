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

int load_from_file(SDL_Renderer **renderer, LTexture *texture, char *path)
{
  free_texture(texture);

  SDL_Texture *new_texture = NULL;

  SDL_Surface *loaded_surface = IMG_Load(path);
  if (loaded_surface == NULL) {
    printf("Failed to load image %s. SDL_IMG error: %s\n", path, IMG_GetError());
    return 0;
  }

  SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xff, 0xff));

  new_texture = SDL_CreateTextureFromSurface(*renderer, loaded_surface);
  if (new_texture == NULL) {
    return 0;
  }

  texture->m_width = loaded_surface->w;
  texture->m_height = loaded_surface->h;

  SDL_FreeSurface(loaded_surface);

  texture->m_texture = new_texture;

  return 1;
}

void free_texture(LTexture *texture)
{
  if (texture && texture->m_texture) {
    SDL_DestroyTexture(texture->m_texture);
    initialize(texture);
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
