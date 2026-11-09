#pragma once
#include <vector>
#include "Cell.h"
#include "Globals.h"
#include "Engine/Random.h"

class Grid {
public:
  Grid(Assets& assetList) {
    using namespace Config;

    cells.reserve(GRID_ROWS * GRID_COLUMNS);

    for (int r{0}; r < GRID_ROWS; ++r) {
      for (int c{0}; c < GRID_COLUMNS; ++c) {
        cells.emplace_back(Cell{r, c, assetList});
      }
    }
  }

  void HandleEvent(const SDL_Event& event) {
    for (auto& cell : cells) {
      cell.HandleEvent(event);
    }
    if (event.type == UserEvents::APPLE_EATEN) {
      PlaceRandomApple();
    }
  }

  void Tick(Uint64 deltaTime) {
    for (auto& cell : cells) {
      cell.Tick(deltaTime);
    }
  }

  void Render(SDL_Surface* surface) {
    for (auto& cell : cells) {
      cell.Render(surface);
    }
  }

private:
  std::vector<Cell> cells;

  void PlaceRandomApple() {
    while (true) {
      int randomIndex{
        Engine::Random::Int(0, int(cells.size()) - 1)
      };
      if (cells[randomIndex].PlaceApple()) {
        break;
      }
    }
  }
};