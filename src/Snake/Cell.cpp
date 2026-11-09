#include "Cell.h"

Cell::Cell(int row, int column, Assets& assetList)
    : row(row),
      column(column),
      assetList{assetList},
      backgroundRect{
        column * Config::CELL_SIZE + Config::PADDING,
        row * Config::CELL_SIZE + Config::PADDING,
        Config::CELL_SIZE,
        Config::CELL_SIZE
      },
      backgroundColor{
        (row + column) % 2 == 0
          ? Config::CELL_COLOR_A
          : Config::CELL_COLOR_B
      }
{
  Initialize();
}

void Cell::HandleEvent(const SDL_Event &event) {
  if (event.type == UserEvents::ADVANCE) {
    Advance(event.user);
  } else if (event.type == UserEvents::APPLE_EATEN) {
    if (state == CellState::Snake) {
      ++snakeDuration;
    }
  }
}

void Cell::Tick(Uint64 deltaTime) {}

void Cell::Render(SDL_Surface *surface) {
  const SDL_PixelFormatDetails *fmt = SDL_GetPixelFormatDetails(surface->format);

  Uint32 bgColor = SDL_MapRGB(
      fmt,
      nullptr,
      backgroundColor.r,
      backgroundColor.g,
      backgroundColor.b
  );
  
  SDL_FillSurfaceRect(surface, &backgroundRect, bgColor);

  if (state == CellState::Apple) {
    assetList.Apple.Render(surface, &backgroundRect);

  } else if (state == CellState::Snake) {
    Uint32 snakeColor = SDL_MapRGB(
        fmt,
        nullptr,
        Config::SNAKE_COLOR.r,
        Config::SNAKE_COLOR.g,
        Config::SNAKE_COLOR.b
      );
    SDL_FillSurfaceRect(surface, &backgroundRect, snakeColor);

  }
}

void Cell::Initialize() {
  
  state = CellState::Empty;
  snakeDuration = 0;

  int middleRow{Config::GRID_ROWS / 2};

  if (row == middleRow && column == 2) {
    state = CellState::Snake;
    snakeDuration = 1;
  } else if (row == middleRow && column == 3) {
    state = CellState::Snake;
    snakeDuration = 2;
  } else if (row == middleRow && column == 11) {
    state = CellState::Apple;
  }
}

void Cell::Advance(const SDL_UserEvent& event) {
  SnakeData* data{ static_cast<SnakeData*>(event.data1) };
  // TODO - Update Cell
  bool isThisCell{
    data->headRow == row &&
    data->headCol == column
  };

  if (isThisCell) {
    if (state == CellState::Apple) {
      SDL_Event newEvent{ .type = UserEvents::APPLE_EATEN };
      SDL_PushEvent(&newEvent);
    }
    state = CellState::Snake;
    snakeDuration = data->length;
  } else if (state == CellState::Snake) {
    --snakeDuration;
    if (snakeDuration == 0) {
      state = CellState::Empty;
    }
  }
}

bool Cell::PlaceApple() {
  if (state != CellState::Empty) return false;

  state = CellState::Apple;
  return true;
}