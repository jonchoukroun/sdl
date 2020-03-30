#include "main.h"

int main()
{
  if (init_sdl() != 1) {
    return -1;
  }

  if (init_sdl_img() != 1) {
    return -1;
  }

  SDL_Window *window = NULL;
  if (init_window(&window, "Lesson 10 - Textures & Transparency") != 1) {
    return -1;
  }

  SDL_Renderer *renderer = NULL;
  if (init_renderer(&window, &renderer) != 1) {
    return -1;
  }

  LTexture *foo_texture = malloc(sizeof(LTexture *));
  LTexture *bg_texture = malloc(sizeof(LTexture *));
  foo_texture->m_texture = NULL;
  bg_texture->m_texture = NULL;

  if (load_media(&renderer, foo_texture, bg_texture) != 1) {
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

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer);

    render(&renderer, bg_texture, 0, 0);

    render(&renderer, foo_texture, 240, 190);

    SDL_RenderPresent(renderer);
  }

  return 0;
}

int init_sdl()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialize SDL. Error: %s\n", SDL_GetError());
    return 0;
  }

  return 1;
}

int init_sdl_img()
{
  int img_flags = IMG_INIT_PNG;
  if (!(IMG_Init(img_flags) & img_flags)) {
    printf("Failed to initialize SDL Image. SDL_IMG error: %s\n", IMG_GetError());
    return 0;
  }

  return 1;
}

int init_window(SDL_Window **window, char * title)
{
  *window = SDL_CreateWindow(title,
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH,
                            SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN);
  if (*window == NULL) {
    printf("Failed to create window. Error: %s\n", SDL_GetError());
    return 0;
  }

  return 1;
}

int init_renderer(SDL_Window **window, SDL_Renderer **renderer)
{
  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
  if (*renderer == NULL) {
    printf("Failed to create renderer. Error: %s\n", SDL_GetError());
    return 0;
  }

  SDL_SetRenderDrawColor(*renderer, 0xff, 0xff, 0xff, 0xff);

  return 1;
}

int load_media(SDL_Renderer **renderer, LTexture *foo_texture, LTexture *bg_texture)
{
  if (load_from_file(renderer, foo_texture, "assets/foo.png") != 1) {
    printf("Failed to load Foo texture image\n");
    return 0;
  }

  if (load_from_file(renderer, bg_texture, "assets/background.png") != 1) {
    printf("Failed to load background texture image\n");
    return 0;
  }

  return 1;
}

void close_renderer(SDL_Window **window, SDL_Renderer **renderer, LTexture *foo_texture, LTexture *bg_texture)
{
  free_texture(foo_texture);
  free_texture(bg_texture);

  SDL_DestroyRenderer(*renderer);
  SDL_DestroyWindow(*window);

  IMG_Quit();
  SDL_Quit();
}
