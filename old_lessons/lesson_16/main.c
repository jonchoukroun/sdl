#include "main.h"

int main()
{
  if (init_sdl() != 1) {
    return -1;
  }

  if (init_sdl_img() != 1) {
    return -1;
  }

  if (init_sdl_ttf() != 1) {
    return -1;
  }

  SDL_Window *window = NULL;
  if (init_window(&window, "Lesson 16 - True Type Fonts") != 1) {
    return -1;
  }

  SDL_Renderer *renderer = NULL;
  if (init_renderer(&window, &renderer) != 1) {
    return -1;
  }

  LTexture *texture = malloc(sizeof(LTexture *));
  texture->m_texture = NULL;

  TTF_Font *font = NULL;
  if (load_media(&renderer, &font, texture) != 1) {
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

    SDL_SetRenderDrawColor(renderer, 0x23, 0x32, 0x11, 0xff);
    SDL_RenderClear(renderer);

    render(&renderer, texture);

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

int init_sdl_ttf()
{
  if (TTF_Init() == -1) {
    printf("Failed to initialize SDL_ttf. SDL-ttf error: %s\n", TTF_GetError());
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
  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (*renderer == NULL) {
    printf("Failed to create renderer. Error: %s\n", SDL_GetError());
    return 0;
  }

  return 1;
}

int load_media(SDL_Renderer **renderer, TTF_Font **font, LTexture *texture)
{
  *font = TTF_OpenFont("fonts/lazy.ttf", 15);
  if (font == NULL) {
    printf("Failed to load font. SDL_ttf error: %s\n", TTF_GetError());
    return 0;
  }

  SDL_Color text_color = {50, 100, 140, 200};
  if (!load_from_rendered_text(renderer, texture, font, text_color, "Hey nong man")) {
    printf("Failed to render text texture.\n");
    return 0;
  }

  return 1;
}

void close_renderer(SDL_Window **window, SDL_Renderer **renderer, LTexture *texture, TTF_Font **font)
{
  free_texture(texture);

  TTF_CloseFont(*font);

  SDL_DestroyRenderer(*renderer);
  SDL_DestroyWindow(*window);

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
