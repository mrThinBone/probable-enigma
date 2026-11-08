#pragma once
#include <SDL3/SDL.h>
#include "Globals.h"
#include "Minesweeper/Grid.h"

class MinesweeperUI {
public:
  void Render(SDL_Surface* surface){
    grid.Render(surface);
  }

  void HandleEvent(const SDL_Event& e){
    grid.HandleEvent(e);
  };

private:
  MinesweeperGrid grid{
    Config::PADDING, Config::PADDING
  };
};