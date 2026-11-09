#pragma once
#include <SDL3/SDL.h>
#include "Globals.h"
#include "SnakeData.h"

class GameState {
public:

  void HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
      HandleKeyEvent(event.key);
    } else if (event.type == UserEvents::APPLE_EATEN) {
      ++snake.length;
      if (snake.length == Config::MAX_LENGTH) {
        SDL_Event newEvent{};
        newEvent.type = UserEvents::GAME_WON;
        SDL_PushEvent(&newEvent);
      }
    } else if (event.type == UserEvents::RESTART_GAME) {
      RestartGame();
    } else if (event.type == UserEvents::GAME_LOST ||
               event.type == UserEvents::GAME_WON) {
      isGameOver = true;
    }
  }

  void Tick(Uint64 deltaTime) {
    if (isPaused || isGameOver) return;

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
  bool isGameOver{false};

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

    if (
      snake.headRow < 0 ||
      snake.headRow >= Config::GRID_ROWS ||
      snake.headCol < 0 ||
      snake.headCol >= Config::GRID_COLUMNS
    ) {
      SDL_Event Event{};
      Event.type = UserEvents::GAME_LOST;
      SDL_PushEvent(&Event);
    } else {
      // If we're not going outside the bounds
      // of the grid, advance as before
      SDL_Event event{};
      event.type = UserEvents::ADVANCE;
      event.user.data1 = &snake;
      SDL_PushEvent(&event);
    }
  }

  void HandleKeyEvent(const SDL_KeyboardEvent& event) {
    if (isGameOver) return;

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
    isPaused = true;
    isGameOver = false;
    elapsedTime = 0;

    snake.headRow = Config::GRID_ROWS / 2;
    snake.headCol = 3;
    snake.length = 2;
    snake.direction = Right;

    nextDirection = Right;
  }
};