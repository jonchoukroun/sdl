#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int init_renderer();
SDL_Texture *load_texture(char *);
void close_renderer();

SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Texture *g_texture = NULL;

int main()
{
  if (init_renderer() != 1) {
    return -1;
  }

  int quit = 0;
  SDL_Event e;
  while (quit != 1) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
        quit = 1;
      }
    }

    SDL_SetRenderDrawColor(g_renderer, 0xd, 0xd, 0xd, 0xff);
    SDL_RenderClear(g_renderer);

    SDL_Rect fill_rect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    SDL_SetRenderDrawColor(g_renderer, 0x29, 0xab, 0x87, 0xc4);
    SDL_RenderFillRect(g_renderer, &fill_rect);

    SDL_Rect outline_rect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
    SDL_SetRenderDrawColor(g_renderer, 0xff, 0xff, 0x00, 0xff);
    SDL_RenderDrawRect(g_renderer, &outline_rect);

    SDL_SetRenderDrawColor(g_renderer, 0x00, 0x32, 0xd8, 0xff);
    SDL_RenderDrawLine(g_renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

    SDL_SetRenderDrawColor(g_renderer, 0xc4, 0x00, 0x12, 0xff);
    for (int i = SCREEN_HEIGHT / 4; i < (SCREEN_HEIGHT / 4) * 3; i += 4) {
      SDL_RenderDrawPoint(g_renderer, SCREEN_WIDTH / 2, i);
    }

    SDL_RenderPresent(g_renderer);
  }

  return 0;
}

int init_renderer()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialize SDL. Error: %s\n", SDL_GetError());
    return 0;
  }

  g_window = SDL_CreateWindow("SDL Tuts",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

  if (g_window == NULL) {
    printf("Failed to create window. Error: %s\n", SDL_GetError());
    return 0;
  }

  g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
  if (g_renderer == NULL) {
    printf("Failed to create renderer. Error: %s\n", SDL_GetError());
    return 0;
  }

  SDL_SetRenderDrawColor(g_renderer, 0x29, 0xAB, 0x87, 0xFF);

  int img_flags = IMG_INIT_PNG;
  if (!(IMG_Init(img_flags) & img_flags)) {
    printf("Failed to initialize SDL Image. SDL_Image Error: %s\n", IMG_GetError());
    return 0;
  }

  return 1;
}

SDL_Texture *load_texture(char *path)
{
  SDL_Texture *new_texture = NULL;
  SDL_Surface *loaded_surface = IMG_Load(path);
  if (loaded_surface == NULL) {
    printf("Failed to load image. SDL_Image Error: %s\n", IMG_GetError());
  } else {
    new_texture = SDL_CreateTextureFromSurface(g_renderer, loaded_surface);
    if (new_texture == NULL) {
      printf("Failed to create texture from %s. Error: %s\n", path, SDL_GetError());
    }

    SDL_FreeSurface(loaded_surface);
  }

  return new_texture;
}

void close_renderer()
{
  SDL_DestroyTexture(g_texture);
  g_texture = NULL;

  SDL_DestroyRenderer(g_renderer);
  SDL_DestroyWindow(g_window);
  g_renderer = NULL;
  g_window = NULL;

  IMG_Quit();
  SDL_Quit();
}
