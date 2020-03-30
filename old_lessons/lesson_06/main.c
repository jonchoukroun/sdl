#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

enum KeyPressSurface {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

int init_renderer();
int load_media();
void close_renderer();
SDL_Surface * load_surface(char *);

SDL_Window *g_window = NULL;
SDL_Surface *g_screen_surface = NULL;
SDL_Surface *g_key_press_surfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface *g_current_surface = NULL;

int main()
{
  if (init_renderer() != 1) {
    printf("Failed to initialize!\n");
  } else {
    if (load_media() != 1) {
      printf("Failed to load media!\n");
    } else {
      g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];
      SDL_BlitSurface(g_current_surface, NULL, g_screen_surface, NULL);
      SDL_UpdateWindowSurface(g_window);

      int quit = 0;
      SDL_Event e;
      while (quit == 0) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = 1;
          } else if (e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
              case SDLK_q:
                quit = 1;
                break;

              case SDLK_UP:
                g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_UP];
                break;

              case SDLK_DOWN:
                g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN];
                break;

              case SDLK_LEFT:
                g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT];
                break;

              case SDLK_RIGHT:
                g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT];
                break;

              default:
                g_current_surface = g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];
                break;
            }
          }
        }

        SDL_BlitSurface(g_current_surface, NULL, g_screen_surface, NULL);
        SDL_UpdateWindowSurface(g_window);
      }
    }
  }
  close_renderer();

  return 0;
}

int init_renderer()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialize SDL. Error: %s\n", SDL_GetError());
    return 0;
  }

  g_window = SDL_CreateWindow("Lesson 2",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

  if (g_window == NULL) {
    printf("Failed to create window. Error: %s\n", SDL_GetError());
    return 0;
  }

  int img_flags = IMG_INIT_PNG;
  if (!(IMG_Init(img_flags) & img_flags)) {
    printf("Failed to initialize SDL Image. SDL_Image Error: %s\n", IMG_GetError());
    return 0;
  }

  g_screen_surface = SDL_GetWindowSurface(g_window);

  return 1;
}

int load_media()
{
  int success = 1;

  g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] = load_surface("assets/machete.png");
  if (g_key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    printf("Failed to load default image\n");
    success = 0;
  }

  g_key_press_surfaces[KEY_PRESS_SURFACE_UP] = load_surface("assets/up.bmp");
  if (g_key_press_surfaces[KEY_PRESS_SURFACE_UP] == NULL) {
    printf("Failed to load up image\n");
    success = 0;
  }

  g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN] = load_surface("assets/down.bmp");
  if (g_key_press_surfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
    printf("Failed to load down image\n");
    success = 0;
  }

  g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT] = load_surface("assets/left.bmp");
  if (g_key_press_surfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
    printf("Failed to load left image\n");
    success = 0;
  }

  g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] = load_surface("assets/right.bmp");
  if (g_key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
    printf("Failed to load right image\n");
    success = 0;
  }

  return success;
}

SDL_Surface * load_surface(char *path)
{
  SDL_Surface *optimized_surface = NULL;
  SDL_Surface *loaded_surface = IMG_Load(path);

  if (loaded_surface == NULL) {
    printf("Failed to load image. SDL_Image Errors: %s\n", IMG_GetError());
  } else {
    optimized_surface = SDL_ConvertSurface(loaded_surface, g_screen_surface->format, 0);

    if (optimized_surface == NULL) {
      printf("Failed to convert image to optimized format. Error: %s\n", SDL_GetError());
    }
  }

  SDL_FreeSurface(loaded_surface);

  return optimized_surface;
}

void close_renderer()
{
  SDL_FreeSurface(g_current_surface);
  g_current_surface = NULL;

  for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
    g_key_press_surfaces[i] = NULL;
  }

  SDL_DestroyWindow(g_window);
  g_window = NULL;

  SDL_Quit();
}
