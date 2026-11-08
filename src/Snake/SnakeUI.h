#pragma once
#include <SDL3/SDL.h>
#include "Assets.h"

class SnakeUI {
 public:
  void HandleEvent(const SDL_Event& event) {}
  void Tick(Uint64 deltaTime) {}
  void Render(SDL_Surface* surface) {}

 private:
  Assets assetList;
};