#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int init_renderer(SDL_Window **, SDL_Renderer **);
int load_media(SDL_Renderer **, SDL_Texture **);
int load_texture(SDL_Renderer **, SDL_Texture **, char *);
void close_renderer(SDL_Window **, SDL_Renderer **, SDL_Texture **);

int main()
{
  SDL_Window *window = malloc(sizeof(SDL_Window *));
  SDL_Renderer *renderer = malloc(sizeof(SDL_Renderer *));
  SDL_Texture *texture = malloc(sizeof(SDL_Texture *));

  if (init_renderer(&window, &renderer) != 1) {
    return -1;
  }

  if (load_media(&renderer, &texture) != 1) {
    return -1;
  }

  SDL_Rect top_left_vp = {
    0,
    0,
    SCREEN_WIDTH / 2,
    SCREEN_HEIGHT / 2
  };

  SDL_Rect top_right_vp = {
    SCREEN_WIDTH / 2,
    0,
    SCREEN_WIDTH / 2,
    SCREEN_HEIGHT / 2
  };

  SDL_Rect bottom_vp = {
    0,
    SCREEN_HEIGHT / 2,
    SCREEN_WIDTH,
    SCREEN_HEIGHT / 2
  };

  int quit = 0;
  SDL_Event e;
  while (quit != 1) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
        quit = 1;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer);

    SDL_RenderSetViewport(renderer, &top_left_vp);
    SDL_Rect purple_box = { 0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    SDL_SetRenderDrawColor(renderer, 0xab, 0x29, 0x87, 0x9c);
    SDL_RenderFillRect(renderer, &purple_box);
    // SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_RenderSetViewport(renderer, &top_right_vp);
    SDL_Rect green_box = { 0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    SDL_SetRenderDrawColor(renderer, 0x29, 0xab, 0x87, 0x9c);
    SDL_RenderFillRect(renderer, &green_box);
    // SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_RenderSetViewport(renderer, &bottom_vp);
    SDL_Rect yellow_box = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_SetRenderDrawColor(renderer, 0x87, 0x87, 0xab, 0x9c);
    SDL_RenderFillRect(renderer, &yellow_box);
    // SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_RenderSetViewport(renderer, NULL);

    SDL_RenderPresent(renderer);
  }

  close_renderer(&window, &renderer, &texture);
  window = NULL;
  renderer = NULL;
  texture = NULL;

  return 0;
}

int init_renderer(SDL_Window ** window, SDL_Renderer **renderer)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialize SDL. Error: %s\n", SDL_GetError());
    return 0;
  }

  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");

  *window = SDL_CreateWindow("SDL Tuts",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

  if (*window == NULL) {
    printf("Failed to create window. Error: %s\n", SDL_GetError());
    return 0;
  }

  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
  if (*renderer == NULL) {
    printf("Failed to create renderer. Error: %s\n", SDL_GetError());
    return 0;
  }

  SDL_SetRenderDrawColor(*renderer, 0x29, 0xAB, 0x87, 0xFF);

  int img_flags = IMG_INIT_PNG;
  if (!(IMG_Init(img_flags) & img_flags)) {
    printf("Failed to initialize SDL Image. SDL_Image Error: %s\n", IMG_GetError());
    return 0;
  }

  return 1;
}

int load_media(SDL_Renderer **renderer, SDL_Texture **texture)
{
  if (load_texture(renderer, texture, "assets/future-butcher.png") != 1) {
    return 0;
  }

  return 1;
}

int load_texture(SDL_Renderer **renderer, SDL_Texture **texture, char *path)
{
  SDL_Surface *loaded_surface = IMG_Load(path);
  if (loaded_surface == NULL) {
    printf("Failed to load image. SDL_Image Error: %s\n", IMG_GetError());
    return 0;
  }

  *texture = SDL_CreateTextureFromSurface(*renderer, loaded_surface);
  if (*texture == NULL) {
    printf("Failed to create texture from %s. Error: %s\n", path, SDL_GetError());
    return 0;
  }

  SDL_FreeSurface(loaded_surface);

  return 1;
}

void close_renderer(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture)
{
  SDL_DestroyTexture(*texture);

  SDL_DestroyRenderer(*renderer);
  SDL_DestroyWindow(*window);

  IMG_Quit();
  SDL_Quit();
}
