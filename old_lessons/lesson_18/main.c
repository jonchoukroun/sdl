#include "main.h"

int main()
{
  if (init_sdl() != 1) return -1;

  if (init_sdl_img() != 1) return -1;

  SDL_Window *window = NULL;
  if (init_window(&window, "Lesson 18 - Key Events") != 1) return -1;

  SDL_Renderer *renderer = NULL;
  if (init_renderer(&window, &renderer) != 1) return -1;

  // array of pointers to LTexture structs
  LTexture *key_press_textures[KEY_PRESS_SURFACE_TOTAL];

  if (load_media(&renderer, key_press_textures) != 1) return -1;

  int quit = 0;
  SDL_Event event;
  LTexture *current_texture = NULL;
  while (quit == 0) {
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = 1;
      }
    }

    const Uint8 *current_key_states = SDL_GetKeyboardState(NULL);
    if (current_key_states[SDL_SCANCODE_Q]) {
      quit = 1;
    }

    if (current_key_states[SDL_SCANCODE_UP]) {
      current_texture = key_press_textures[KEY_PRESS_SURFACE_UP];
    } else if (current_key_states[SDL_SCANCODE_DOWN]) {
      current_texture = key_press_textures[KEY_PRESS_SURFACE_DOWN];
    } else if (current_key_states[SDL_SCANCODE_LEFT]) {
      current_texture = key_press_textures[KEY_PRESS_SURFACE_LEFT];
    } else if (current_key_states[SDL_SCANCODE_RIGHT]) {
      current_texture = key_press_textures[KEY_PRESS_SURFACE_RIGHT];
    } else {
      current_texture = key_press_textures[KEY_PRESS_SURFACE_DEFAULT];
    }

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer);

    render_texture(&renderer, current_texture, 0, 0, NULL);

    SDL_RenderPresent(renderer);
  }

  close_renderer(&window, &renderer, key_press_textures);

  return 0;
}

int init_sdl()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialize SDL. SDL error: %s\n", SDL_GetError());
    return 0;
  }

  return 1;
}

int init_sdl_img()
{
  int img_flags = IMG_INIT_PNG;
  if (!(IMG_Init(img_flags) & img_flags)) {
    printf("Failed to initialize SDL Image. Error: %s\n", IMG_GetError());
    return 0;
  }

  return 1;
}

int init_window(SDL_Window **window, char *title)
{
  *window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf("Failed to create window. SDL error: %s\n", SDL_GetError());
    return 0;
  }

  return 1;
}

int init_renderer(SDL_Window **window, SDL_Renderer **renderer)
{
  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED / SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) {
    printf("Failed to create renderer. SDL error: %s\n", SDL_GetError());
    return 0;
  }

  return 1;
}

int create_surface(SDL_Window **window, SDL_Surface **surface)
{
  *surface = SDL_GetWindowSurface(*window);
  if (surface == NULL) {
    printf("Failed to get window's surface. SDL error: %s\n", SDL_GetError());
    return 0;
  }

  return 1;
}

SDL_Surface load_surface(char *path)
{
  SDL_Surface *loaded_surface = SDL_LoadBMP(path);

  if (loaded_surface == NULL) {
    printf("Failed to load surface from %s. SDL error: %s\n", path, SDL_GetError());
  }

  return *loaded_surface;
}

int load_media(SDL_Renderer **renderer, LTexture *key_press_textures[])
{
  LTexture *default_texture = malloc(sizeof(LTexture));
  init_texture(default_texture);
  if (load_from_file(renderer, default_texture, "assets/press.bmp") != 1) {
    printf("Failed to load default image\n");
    return 0;
  }
  key_press_textures[KEY_PRESS_SURFACE_DEFAULT] = default_texture;

  LTexture *left_texture = malloc(sizeof(LTexture));
  init_texture(left_texture);
  if (load_from_file(renderer, left_texture, "assets/left.bmp") != 1) {
    printf("Failed to load left image\n");
    return 0;
  }
  key_press_textures[KEY_PRESS_SURFACE_LEFT] = left_texture;

  LTexture *right_texture = malloc(sizeof(LTexture));
  init_texture(right_texture);
  if (load_from_file(renderer, right_texture, "assets/right.bmp") != 1) {
    printf("Failed to load right image\n");
    return 0;
  }
  key_press_textures[KEY_PRESS_SURFACE_RIGHT] = right_texture;

  LTexture *down_texture = malloc(sizeof(LTexture));
  init_texture(down_texture);
  if (load_from_file(renderer, down_texture, "assets/down.bmp") != 1) {
    printf("Failed to load down image\n");
    return 0;
  }
  key_press_textures[KEY_PRESS_SURFACE_DOWN] = down_texture;

  LTexture *up_texture = malloc(sizeof(LTexture));
  init_texture(up_texture);
  if (load_from_file(renderer, up_texture, "assets/up.bmp") != 1) {
    printf("Failed to load up image\n");
    return 0;
  }
  key_press_textures[KEY_PRESS_SURFACE_UP] = up_texture;

  return 1;
}

void close_renderer(SDL_Window **window, SDL_Renderer **renderer, LTexture *key_press_textures[])
{
  for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
    free(key_press_textures[i]);
  }

  SDL_DestroyRenderer(*renderer);
  SDL_DestroyWindow(*window);

  SDL_Quit();
}
