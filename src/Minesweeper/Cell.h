#pragma once
#include <SDL3/SDL.h>
#include "Engine/Button.h"

class MinesweeperCell : public Engine::Button {
public:
  MinesweeperCell(
    int x, int y, int w, int h, int row, int col
  );

  void HandleEvent(const SDL_Event& e) override;
  void Render(SDL_Surface* surface) override;

  int GetRow() const{ return row; }

  int GetCol() const{ return col; }

protected:
  void HandleLeftClick() override;

private:
  int row;
  int col;
  bool isCleared{false};

  void ClearCell();
  
};