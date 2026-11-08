#pragma once
#include <SDL3/SDL.h>
#include "Assets.h"

enum class CellState { Snake, Apple, Empty };

class Cell {
public:
  Cell(int row, int column, Assets& assetList);

  void HandleEvent(const SDL_Event& event);
  void Tick(Uint64 deltaTime);
  void Render(SDL_Surface* surface);

private:
  int row;
  int column;
  Assets& assetList;
  SDL_Rect backgroundRect;
  SDL_Color backgroundColor;
  CellState state;

  void Initialize();
};