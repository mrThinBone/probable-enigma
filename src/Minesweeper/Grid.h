#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include "Globals.h"
#include "Minesweeper/Cell.h"

class MinesweeperGrid {
public:
  MinesweeperGrid(int x, int y){
    using namespace Config;
    children.reserve(GRID_COLUMNS * GRID_ROWS);
    for (int col{1}; col <= GRID_COLUMNS; ++col) {
      for (int row{1}; row <= GRID_ROWS; ++row) {
        constexpr int spacing{CELL_SIZE + PADDING};
        children.emplace_back(
          x + (spacing) * (col - 1),
          y + (spacing) * (row - 1),
          CELL_SIZE, CELL_SIZE, row, col
        );
      }
    }
  }

  void Render(SDL_Surface* Surface){
    for (auto& child : children) {
      child.Render(Surface);
    }
  }

  void HandleEvent(const SDL_Event& E){
    for (auto& child : children) {
      child.HandleEvent(E);
    }
  }

  std::vector<MinesweeperCell> children;
};