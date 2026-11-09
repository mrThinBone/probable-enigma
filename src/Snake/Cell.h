#pragma once
#include <SDL3/SDL.h>
#include "Assets.h"
#include "SnakeData.h"

enum class CellState { Snake, Apple, Empty };

class Cell {
public:
  Cell(int row, int column, Assets& assetList);

  void HandleEvent(const SDL_Event& event);
  void Tick(Uint64 deltaTime);
  void Render(SDL_Surface* surface);

  bool PlaceApple();

private:
  int row;
  int column;
  Assets& assetList;
  SDL_Rect backgroundRect;
  SDL_Color backgroundColor;
  CellState state;

  /*
  1. When a cell becomes the snake's head, we set its duration to the snake's total length.
  2. Every game advance decrements the duration of all snake cells.
  3. When a cell's duration reaches zero, it reverts to an empty cell.
  This system handles the snake's movement:
    New head segments get the full snake length as their duration.
    Tail segments naturally disappear when their duration expires.
    The snake maintains its length as it moves.
  */
  int snakeDuration{0};

  void Initialize();
  void Advance(const SDL_UserEvent& event);
};