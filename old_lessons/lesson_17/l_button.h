#include <SDL2/SDL.h>

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 200
#define TOTAL_BUTTONS 4

typedef enum LButtonSprite {
  BUTTON_SPRITE_MOUSE_OUT = 0,
  BUTTON_SPRITE_MOUSE_OVER = 1,
  BUTTON_SPRITE_MOUSE_DOWN = 2,
  BUTTON_SPRITE_MOUSE_UP = 3,
  BUTTON_SPRITE_TOTAL = 4
} LButtonSprite;

typedef struct LButton {
  SDL_Point *position;
  LButtonSprite current_sprite;
} LButton;

void initialize_button(LButton *);

void set_position(LButton *, int x, int y);

void handle_mouse_event(LButton *, SDL_Event *);
