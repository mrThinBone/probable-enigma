#pragma once
#include <SDL3/SDL.h>
#include "../Globals.h"
#include "SnakeData.h"

class GameState {
public:

  void Handleevent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
      HandleKeyEvent(event.key);
    }
  }

  void Tick(Uint64 deltaTime) {
    elapsedTime += deltaTime;
    if (elapsedTime >= Config::ADVANCE_INTERVAL) {
      elapsedTime = 0;
      Updatesnake();
    }
  }

private:
  SnakeData snake{ Config::GRID_ROWS / 2, 3, 2, Right };
  Uint64 elapsedTime{0};
  // Direction the snake will move in when the
  // game state next advances
  MovementDirection nextDirection{Right};

  void Updatesnake() {
    snake.direction = nextDirection;
    switch (nextDirection) {
      case Up:
        snake.headRow--;
        break;
      case Down:
        snake.headRow++;
        break;
      case Left:
        snake.headCol--;
        break;
      case Right:
        snake.headCol++;
        break;
    }

    SDL_Event event{};
    event.type = UserEvents::ADVANCE;
    event.user.data1 = &snake;
    SDL_PushEvent(&event);
  }

  void HandleKeyEvent(const SDL_KeyboardEvent& event) {
    switch (event.key) {
      case SDLK_UP:
      case SDLK_W:
        if (snake.Direction != Down) {
          nextDirection = Up;
        }
        break;
      case SDLK_DOWN:
      case SDLK_S:
        if (snake.Direction != Up) {
          nextDirection = Down;
        }
        break;
      case SDLK_LEFT:
      case SDLK_A:
        if (snake.Direction != Right) {
          nextDirection = Left;
        }
        break;
      case SDLK_RIGHT:
      case SDLK_D:
        if (snake.Direction != Left) {
          nextDirection = Right;
        }
        break;
    }
  }
};