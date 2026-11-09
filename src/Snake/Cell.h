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

  void Reset();

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

  /* snake animation var */
  SDL_Rect snakeRect;
  // ontrolling how far the snake has slid across our cell
  // as how much of the cell the snake occupies, ranging from 0.0 (empty) to 1.0 (completely full)
  float fillPercent{0.0f};

  // indicates where the snake enters the cell (Up, Down, Left, or Right).
  MovementDirection fillDirection{Right};

  void GrowHead(float deltaTime);
  void ShrinkTail(float deltaTime);

  void Advance(const SDL_UserEvent& event);
};