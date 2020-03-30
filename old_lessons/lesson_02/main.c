#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int init_renderer(SDL_Window **, SDL_Surface **);
int load_media(SDL_Surface **image);
void close_renderer(SDL_Window **, SDL_Surface **image);

int main()
{
  SDL_Window *window = (SDL_Window *)malloc(sizeof(SDL_Window *));
  SDL_Surface *surface = (SDL_Surface *)malloc(sizeof(SDL_Surface *));
  SDL_Surface *image = (SDL_Surface *)malloc(sizeof(SDL_Surface *));

  if (init_renderer(&window, &surface) != 1) {
    printf("Failed to initialize!\n");
    return -1;
  }

  if (load_media(&image) != 1) {
    printf("Failed to load media!\n");
    return -1;
  }

  SDL_BlitSurface(image, NULL, surface, NULL);
  SDL_UpdateWindowSurface(window);

  int quit = 0;
  SDL_Event e;
  while (quit == 0) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_q) {
        quit = 1;
      }
    }
  }

  close_renderer(&window, &image);

  return 0;
}

int init_renderer(SDL_Window **window, SDL_Surface **surface)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Failed to initialize SDL. Error: %s\n", SDL_GetError());
    return 0;
  }

  *window = SDL_CreateWindow("Lesson 2",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

  if (*window == NULL) {
    printf("Failed to create window. Error: %s\n", SDL_GetError());
    return 0;
  }

  *surface = SDL_GetWindowSurface(*window);

  return 1;
}

int load_media(SDL_Surface **image)
{
  *image = SDL_LoadBMP("assets/background-night.bmp");

  if (*image == NULL) {
    printf("Failed to load image. Error: %s\n", SDL_GetError());
    return 0;
  }

  return 1;
}

void close_renderer(SDL_Window **window, SDL_Surface **image)
{
  SDL_FreeSurface(*image);

  SDL_DestroyWindow(*window);

  SDL_Quit();
}
