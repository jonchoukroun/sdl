#include "l_button.h"

void initialize_button(LButton *button)
{
  SDL_Point *point = malloc(sizeof(SDL_Point));
  button->position = point;
  button->position->x = 0;
  button->position->y = 0;
  button->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
}

void set_position(LButton *button, int x, int y)
{
  button->position->x = x;
  button->position->y = y;
}

void handle_mouse_event(LButton *button, SDL_Event *event)
{
  if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    int is_inside = 1;
    if (x < button->position->x) {
      is_inside = 0;
    } else if (x > button->position->x + BUTTON_WIDTH) {
      is_inside = 0;
    } else if (y < button->position->y) {
      is_inside = 0;
    } else if (y > button->position->y + BUTTON_HEIGHT) {
      is_inside = 0;
    }

    if (is_inside == 0) {
      button->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
      return;
    }

    switch (event->type)
    {
    case SDL_MOUSEMOTION:
      button->current_sprite = BUTTON_SPRITE_MOUSE_OVER;
      break;

    case SDL_MOUSEBUTTONUP:
      button->current_sprite = BUTTON_SPRITE_MOUSE_UP;
      break;

    case SDL_MOUSEBUTTONDOWN:
      button->current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
      break;

    default:
      break;
    }
  }
}
