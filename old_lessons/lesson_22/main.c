#include "main.h"

int main()
{
  if (init_sdl() != 1) return -1;

  if (init_sdl_img() != 1) return -1;

  if (init_ttf_font() != 1) return -1;

  SDL_Window *window = NULL;
  if (init_window(&window, "Lesson 18 - Key Events") != 1) return -1;

  SDL_Renderer *renderer = NULL;
  if (init_renderer(&window, &renderer) != 1) return -1;

  LTexture *prompt_texture = malloc(sizeof(LTexture *));
  LTexture *time_texture = malloc(sizeof(LTexture *));
  init_texture(prompt_texture);
  init_texture(time_texture);

  TTF_Font *font = NULL;
  if (load_media(&renderer, &font, prompt_texture) != 1) return -1;

  SDL_Color text_color = {0, 0, 0, 255};

  Uint32 start_time = 0;
  char *time_text;

  int quit = 0;
  SDL_Event e;
  while (quit == 0) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) quit = 1;

      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym)
        {
        case SDLK_RETURN:
          start_time = SDL_GetTicks();
          break;

        case SDLK_q:
          quit = 1;
          break;

        default:
          break;
        }
      }
    }

    asprintf(&time_text, "Milliseconds since start %d\n", SDL_GetTicks() - start_time);
    if (!load_from_rendered_text(&renderer, time_texture, &font, text_color, time_text)) {
      printf("Failed to render string\n");
    }

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer);

    render_texture(&renderer, prompt_texture, (SCREEN_WIDTH - prompt_texture->m_width) / 2, 0, NULL);
    render_texture(&renderer, time_texture, (SCREEN_WIDTH - prompt_texture->m_width) / 2, (SCREEN_HEIGHT - prompt_texture->m_height) / 2, NULL);

    SDL_RenderPresent(renderer);
  }

  close_renderer(&window, &renderer, &font, prompt_texture);

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

int init_ttf_font()
{
  if(TTF_Init() < 0) {
    printf("Failed to initialize TTF Font. Error: %s\n", TTF_GetError());
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

int load_media(SDL_Renderer **renderer, TTF_Font **font, LTexture *prompt_texture)
{
  *font = TTF_OpenFont("fonts/lazy.ttf", 15);
  if(font == NULL) {
    printf("Failed to load font. Error %s\n", TTF_GetError());
    return 0;
  }

  SDL_Color text_color = {0, 0, 0, 255};
  int result = load_from_rendered_text(renderer, prompt_texture, font, text_color, "Press Enter to reset start time.\n");
  if (result == 0) {
    printf("Failed to render texture from font.\n");
    return 0;
  }

  return 1;
}

void close_renderer(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font, LTexture *prompt_texture)
{
  free_texture(prompt_texture);

  TTF_CloseFont(*font);

  SDL_DestroyRenderer(*renderer);
  SDL_DestroyWindow(*window);

  SDL_Quit();
}
