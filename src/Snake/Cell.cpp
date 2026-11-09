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
  Reset();
}

void Cell::HandleEvent(const SDL_Event &event) {
  if (event.type == UserEvents::ADVANCE) {
    Advance(event.user);
  } else if (event.type == UserEvents::APPLE_EATEN) {
    if (state == CellState::Snake) {
      ++snakeDuration;
    }
  } else if (event.type == UserEvents::RESTART_GAME) {
    Reset();
  }
}

void Cell::Tick(Uint64 deltaTime) {
  if (state == CellState::Snake && fillPercent < 1.0f) {
    GrowHead(float(deltaTime));
  }
  else if (state != CellState::Snake && fillPercent > 0.0f) {
    ShrinkTail(float(deltaTime));
  }
}

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

  // } else if (state == CellState::Snake) {
  } else if (fillPercent > 0.0f) {
    Uint32 snakeColor = SDL_MapRGB(
        fmt,
        nullptr,
        Config::SNAKE_COLOR.r,
        Config::SNAKE_COLOR.g,
        Config::SNAKE_COLOR.b
      );
    SDL_FillSurfaceRect(surface, &snakeRect, snakeColor);

  }
}

void Cell::Reset() {
  snakeRect = backgroundRect;
  
  state = CellState::Empty;
  snakeDuration = 0;

  fillPercent = 0.0f;
  fillDirection = Right;


  int middleRow{Config::GRID_ROWS / 2};

  if (row == middleRow && column == 2) {
    state = CellState::Snake;
    snakeDuration = 1;
    fillPercent = 1.0f;
  } else if (row == middleRow && column == 3) {
    state = CellState::Snake;
    snakeDuration = 2;
    fillPercent = 1.0f;
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
    if (state == CellState::Snake) { // snake hit itself
      SDL_Event newEvent{};
      newEvent.type = UserEvents::GAME_LOST;
      SDL_PushEvent(&newEvent);
      return;
    }

    if (state == CellState::Apple) {
      SDL_Event newEvent{ .type = UserEvents::APPLE_EATEN };
      SDL_PushEvent(&newEvent);
    }
    state = CellState::Snake;
    snakeDuration = data->length;

    fillDirection = data->direction;
    fillPercent = 0.0f;

  } else if (state == CellState::Snake) {
    
    // animate snake tail leaving
    if (snakeDuration == data->length) {
      fillDirection = data->direction;
    }

    --snakeDuration;
    if (snakeDuration == 0) {
      state = CellState::Empty;
    }
  }
}

void Cell::GrowHead(float deltaTime) {
  using namespace Config;
  fillPercent += deltaTime / ADVANCE_INTERVAL;
  if (fillPercent > 1.0f) fillPercent = 1.0f;

  snakeRect = backgroundRect;
  if (fillDirection == Right) {
    snakeRect.w = int(CELL_SIZE * fillPercent);
  } else if (fillDirection == Down) {
    snakeRect.h = int(CELL_SIZE * fillPercent);
  } else if (fillDirection == Left) {
    snakeRect.x = int(backgroundRect.x +
      CELL_SIZE * (1.0f - fillPercent));
  } else if (fillDirection == Up) {
    snakeRect.y = int(backgroundRect.y +
      CELL_SIZE * (1.0f - fillPercent));
  }
}

void Cell::ShrinkTail(float deltaTime) {
  using namespace Config;
  fillPercent -= deltaTime / ADVANCE_INTERVAL;
  if (fillPercent < 0.0f) fillPercent = 0.0f;

  snakeRect = backgroundRect;
  if (fillDirection == Right) {
    snakeRect.x = backgroundRect.x +
      int(CELL_SIZE * (1.0f - fillPercent));
  } else if (fillDirection == Left) {
    snakeRect.w = int(CELL_SIZE * fillPercent);
  } else if (fillDirection == Up) {
    snakeRect.h = int(CELL_SIZE * fillPercent);
  } else if (fillDirection == Down) {
    snakeRect.y = backgroundRect.y +
      int(CELL_SIZE * (1.0f - fillPercent));
  }
}

bool Cell::PlaceApple() {
  if (state != CellState::Empty) return false;

  state = CellState::Apple;
  return true;
}