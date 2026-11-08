// demonstrate tick machenism
#pragma once
#include <SDL3/SDL.h>

class GameObject {
 public:
  virtual void HandleEvent(const SDL_Event& E) {
    // ...
  }

  virtual void Tick(float timeDelta) {
    // ...
  }

  virtual void Render(SDL_Surface* surface) {
    // ...
  }
};