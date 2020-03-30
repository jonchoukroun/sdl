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
  if (init_window(&window, "Lesson 11 - Clip Rendering & Sprite Sheets") != 1) {
    return -1;
  }

  SDL_Renderer *renderer = NULL;
  if (init_renderer(&window, &renderer) != 1) {
    return -1;
  }

  SDL_Rect *sprite_clips = malloc(sizeof(SDL_Rect *) * 4);
  LTexture *sprite_sheet_texture = malloc(sizeof(LTexture *));
  sprite_sheet_texture->m_texture = NULL;


  if (load_media(&renderer, sprite_clips, sprite_sheet_texture) != 1) {
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

    render(&renderer, sprite_sheet_texture, 0, 0, &sprite_clips[0]);
    render(&renderer, sprite_sheet_texture, SCREEN_WIDTH - sprite_clips[1].w, 0, &sprite_clips[1]);
    render(&renderer, sprite_sheet_texture, 0, SCREEN_HEIGHT - sprite_clips[2].h, &sprite_clips[2]);
    render(&renderer, sprite_sheet_texture, SCREEN_WIDTH - sprite_clips[3].w, SCREEN_HEIGHT - sprite_clips[3].h, &sprite_clips[3]);

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

int load_media(SDL_Renderer **renderer, SDL_Rect *sprite_clips, LTexture *sprite_sheet_texture)
{
  if (load_from_file(renderer, sprite_sheet_texture, "assets/dots.png") != 1) {
    printf("Failed to load dots sprite sheet\n");
    return 0;
  }

  sprite_clips[0].x = 0;
  sprite_clips[0].y = 0;
  sprite_clips[0].h = 100;
  sprite_clips[0].w = 100;

  sprite_clips[1].x = 100;
  sprite_clips[1].y = 0;
  sprite_clips[1].h = 100;
  sprite_clips[1].w = 100;

  sprite_clips[2].x = 0;
  sprite_clips[2].y = 100;
  sprite_clips[2].h = 100;
  sprite_clips[2].w = 100;

  sprite_clips[3].x = 100;
  sprite_clips[3].y = 100;
  sprite_clips[3].h = 100;
  sprite_clips[3].w = 100;

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
