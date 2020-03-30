#include "main.h"

int main()
{
  if (init_sdl() != 1) return -1;

  if (init_sdl_img() != 1) return -1;

  if (init_sdl_mixer() != 1) return -1;

  SDL_Window *window = NULL;
  if (init_window(&window, "Lesson 18 - Key Events") != 1) return -1;

  SDL_Renderer *renderer = NULL;
  if (init_renderer(&window, &renderer) != 1) return -1;

  LTexture *texture = malloc(sizeof(LTexture));
  init_texture(texture);
  if (load_image(&renderer, texture) != 1) return -1;

  Mix_Music *music = NULL;
  Mix_Chunk *sfx[TOTAL_SFX];
  if (load_audio(&music, sfx) != 1) return -1;

  int quit = 0;
  SDL_Event event;
  while (quit == 0) {
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = 1;
      }

      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_1:
            Mix_PlayChannel(-1, sfx[HIGH_SFX], 0);
            break;

          case SDLK_2:
            Mix_PlayChannel(-1, sfx[MEDIUM_SFX], 0);
            break;

          case SDLK_3:
            Mix_PlayChannel(-1, sfx[LOW_SFX], 0);
            break;

          case SDLK_4:
            Mix_PlayChannel(-1, sfx[SCRATCH_SFX], 0);
            break;

          case SDLK_9:
            if (Mix_PlayingMusic() == 0) {
              Mix_PlayMusic(music, -1);
            } else {
              if (Mix_PausedMusic() == 1) {
                Mix_ResumeMusic();
              } else {
                Mix_PauseMusic();
              }
            }
            break;

          case SDLK_0:
            Mix_HaltMusic();
            break;

          case SDLK_q:
            quit = 1;
            break;

          default:
            break;
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer);

    render_texture(&renderer, texture, 0, 0, NULL);

    SDL_RenderPresent(renderer);
  }

  close_audio(&music, sfx);
  close_renderer(&window, &renderer, texture);

  return 0;
}

int init_sdl()
{
  int init_flags = SDL_INIT_VIDEO|SDL_INIT_AUDIO;
  if (SDL_Init(init_flags) < 0) {
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

int init_sdl_mixer()
{
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
    printf("Failed to open audio. Error: %s\n", Mix_GetError());
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

int load_image(SDL_Renderer **renderer, LTexture *texture)
{
  if (load_from_file(renderer, texture, "assets/21/img/prompt.png") != 1) {
    printf("Failed to load prompt image\n");
    return 0;
  }

  return 1;
}

int load_audio(Mix_Music **music, Mix_Chunk *sfx[])
{
  *music = Mix_LoadMUS("assets/21/audio/beat.wav");
  if (music == NULL) {
    printf("Failed to load beat music. Error: %s\n", Mix_GetError());
    return 0;
  }

  sfx[SCRATCH_SFX] = Mix_LoadWAV("assets/21/audio/scratch.wav");
  if (sfx[SCRATCH_SFX] == NULL) {
    printf("Failed to load scratch SFX. Error: %s\n", Mix_GetError());
    return 0;
  }

  sfx[HIGH_SFX] = Mix_LoadWAV("assets/21/audio/high.wav");
  if (sfx[HIGH_SFX] == NULL) {
    printf("Failed to load high SFX. Error: %s\n", Mix_GetError());
    return 0;
  }

  sfx[MEDIUM_SFX] = Mix_LoadWAV("assets/21/audio/med.wav");
  if (sfx[MEDIUM_SFX] == NULL) {
    printf("Failed to load medium SFX. Error: %s\n", Mix_GetError());
    return 0;
  }

  sfx[LOW_SFX] = Mix_LoadWAV("assets/21/audio/low.wav");
  if (sfx[LOW_SFX] == NULL) {
    printf("Failed to load low SFX. Error: %s\n", Mix_GetError());
    return 0;
  }

  return 1;
}


void close_audio(Mix_Music **music, Mix_Chunk *sfx[])
{
  Mix_FreeChunk(sfx[SCRATCH_SFX]);
  Mix_FreeChunk(sfx[HIGH_SFX]);
  Mix_FreeChunk(sfx[MEDIUM_SFX]);
  Mix_FreeChunk(sfx[LOW_SFX]);

  Mix_FreeMusic(*music);

  Mix_Quit();
}

void close_renderer(SDL_Window **window, SDL_Renderer **renderer, LTexture *texture)
{
  free_texture(texture);

  SDL_DestroyRenderer(*renderer);
  SDL_DestroyWindow(*window);

  SDL_Quit();
}
