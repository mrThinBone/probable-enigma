#pragma once
#include <SDL3/SDL.h>
#include "Assets.h"
#include "Grid.h"

class SnakeUI {
 public:
  SnakeUI(Assets& assetList) : grid{assetList} {}

  void HandleEvent(const SDL_Event& event) {
    grid.HandleEvent(event);
  }
  void Tick(Uint64 deltaTime) {
    grid.Tick(deltaTime);
  }
  void Render(SDL_Surface* surface) {
    grid.Render(surface);
  }

 private:
  Assets assetList;
  Grid grid;
};