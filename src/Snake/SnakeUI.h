#pragma once
#include <SDL3/SDL.h>
#include "Assets.h"
#include "Grid.h"
#include "RestartButton.h"

class SnakeUI {
 public:
  SnakeUI(Assets& assetList) : grid{assetList},restartBtn{
        Config::WINDOW_WIDTH - 150,
        Config::GRID_HEIGHT + Config::PADDING * 2,
        150 - Config::PADDING,
        Config::FOOTER_HEIGHT - Config::PADDING
      } 
  {
  }

  void HandleEvent(const SDL_Event& event) {
    grid.HandleEvent(event);
    restartBtn.HandleEvent(event);
  }
  void Tick(Uint64 deltaTime) {
    grid.Tick(deltaTime);
  }
  void Render(SDL_Surface* surface) {
    grid.Render(surface);
    restartBtn.Render(surface);
  }

 private:
  Assets assetList;
  Grid grid;
  RestartButton restartBtn;
};