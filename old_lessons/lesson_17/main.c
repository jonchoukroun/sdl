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
  if (init_window(&window, "Lesson 17 - Mouse Events") != 1) {
    return -1;
  }

  SDL_Renderer *renderer = NULL;
  if (init_renderer(&window, &renderer) != 1) {
    return -1;
  }

  LTexture *texture = malloc(sizeof(LTexture));
  texture->m_texture = NULL;

  SDL_Rect *sprite_clips = malloc(BUTTON_SPRITE_TOTAL * sizeof(SDL_Rect));

  LButton *buttons = malloc(TOTAL_BUTTONS * sizeof(LButton *));
  for (int i = 0; i < TOTAL_BUTTONS; ++i) {
    initialize_button(&buttons[i]);
  }

  if (load_media(&renderer, texture, sprite_clips, buttons) != 1) {
    return -1;
  }

  int quit = 0;
  SDL_Event e;
  while (quit != 1) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
        quit = 1;
      }

      for (int i = 0; i < TOTAL_BUTTONS; ++i) {
        handle_mouse_event(&buttons[i], &e);
      }
    }

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer);

    for (int i = 0 ; i < TOTAL_BUTTONS; ++i) {
      render_texture(
        &renderer,
        texture,
        (&buttons[i])->position->x,
        (&buttons[i])->position->y,
        &sprite_clips[(&buttons[i])->current_sprite]);
    }

    SDL_RenderPresent(renderer);
  }

  close_renderer(&window, &renderer, texture);

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
  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (*renderer == NULL) {
    printf("Failed to create renderer. Error: %s\n", SDL_GetError());
    return 0;
  }

  return 1;
}

int load_media(SDL_Renderer **renderer, LTexture *texture, SDL_Rect *sprite_clips, LButton *buttons)
{
  if (!load_from_file(renderer, texture, "assets/buttons.png")) {
    printf("Failed to load button sprite sheet. SDL error: %s\n", SDL_GetError());
    return 0;
  }

  for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
    sprite_clips[i].x = 0;
    sprite_clips[i].y = i * 200;
    sprite_clips[i].w = BUTTON_WIDTH;
    sprite_clips[i].h = BUTTON_HEIGHT;
  }

  set_position(&buttons[0], 0, 0);
  set_position(&buttons[1], SCREEN_WIDTH - BUTTON_WIDTH, 0);
  set_position(&buttons[2], 0, SCREEN_HEIGHT - BUTTON_HEIGHT);
  set_position(&buttons[3], SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);

  return 1;
}

void close_renderer(SDL_Window **window, SDL_Renderer **renderer, LTexture *texture)
{
  free_texture(texture);

  SDL_DestroyRenderer(*renderer);
  SDL_DestroyWindow(*window);

  IMG_Quit();
  SDL_Quit();
}
