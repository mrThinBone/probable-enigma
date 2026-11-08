#include <iostream>
#include <SDL3/SDL.h>
#include "Minesweeper/Cell.h"
#include "Globals.h"

MinesweeperCell::MinesweeperCell(
  int x, int y, int w, int h, int row, int col)
  : Button{x, y, w, h}, row{row}, col{col} {};

void MinesweeperCell::HandleEvent(
  const SDL_Event& e){
  Button::HandleEvent(e);
}

void MinesweeperCell::Render(
  SDL_Surface* surface){
  Button::Render(surface);
}

void MinesweeperCell::HandleLeftClick(){
  ClearCell();
}

void MinesweeperCell::ClearCell(){
  if (isCleared) return;
  isCleared = true;
  SetIsDisabled(true);
  SetColor(Config::BUTTON_CLEARED_COLOR);
}