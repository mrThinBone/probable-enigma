#pragma once
#include <SDL3/SDL.h>
#include "../Globals.h"
#include "SnakeData.h"

class GameState {
public:

  void HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
      HandleKeyEvent(event.key);
    } else if (event.type == UserEvents::APPLE_EATEN) {
      ++snake.length;
    } else if (event.type == UserEvents::RESTART_GAME) {
      RestartGame();
    }
  }

  void Tick(Uint64 deltaTime) {
    if (isPaused) return;

    elapsedTime += deltaTime;

    if (elapsedTime >= Config::ADVANCE_INTERVAL) {
      elapsedTime = 0;
      UpdateSnake();
    }
  }

private:
  SnakeData snake{ Config::GRID_ROWS / 2, 3, 2, Right };
  Uint64 elapsedTime{0};
  // Direction the snake will move in when the
  // game state next advances
  MovementDirection nextDirection{Right};

  bool isPaused{true};

  void UpdateSnake() {
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
        if (snake.direction != Down) {
          nextDirection = Up;
        }
        break;
      case SDLK_DOWN:
      case SDLK_S:
        if (snake.direction != Up) {
          nextDirection = Down;
        }
        break;
      case SDLK_LEFT:
      case SDLK_A:
        if (snake.direction != Right) {
          nextDirection = Left;
        }
        break;
      case SDLK_RIGHT:
      case SDLK_D:
        if (isPaused) {
          isPaused = false;
          nextDirection = Right;
          UpdateSnake();
        } else if (snake.direction != Left) {
          nextDirection = Right;
        }
        break;
    }
  }

  void RestartGame() {
    elapsedTime = 0;

    snake.headRow = Config::GRID_ROWS / 2;
    snake.headCol = 3;
    snake.length = 2;
    snake.direction = Right;

    nextDirection = Right;
  }
};