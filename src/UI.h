#pragma once
#include <SDL3/SDL.h>
#include "Rectangle.h"
#include "Button.h"

class UI {
public:
  void Render(SDL_Surface* surface) const {
    recA.Render(surface);
    recB.Render(surface);
    btnC.Render(surface);
  }

  void HandleEvent(SDL_Event& e) {
    recA.HandleEvent(e);
    recB.HandleEvent(e);
    btnC.HandleEvent(e);
  }

  void SetRectangleColors(const SDL_Color& color) {
    recA.SetColor(color);
    recB.SetColor(color);
  }

private:
  Rectangle recA{SDL_Rect{50, 50, 50, 50}};
  Rectangle recB{SDL_Rect{150, 50, 50, 50}};
  Button btnC{SDL_Rect{250, 50, 50, 50}};
};