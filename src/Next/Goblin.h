#pragma once
#include <string>
#include "GameObject.h"

class Goblin : public GameObject {
 public:
  Goblin(const std::string& name, int x, int y)
    : name(name), xPosition(x), yPosition(y) {}

  std::string name;
  int xPosition;
  int yPosition;
  int velocity{1};

  void HandleEvent(const SDL_Event& E) override {

    if (E.type != SDL_EVENT_KEY_DOWN) return;

    if (E.key.key == SDLK_RIGHT) {
      std::cout << "\nHandleEvent() setting velocity to 1";
      velocity = 1;
    } else if (E.key.key == SDLK_LEFT) {
      std::cout << "\nHandleEvent() setting velocity to -1";
      velocity = -1;
    }
  }

  void Tick(float timeDelta) override {
    xPosition += velocity * timeDelta;
    std::cout << "Goblin position: " << xPosition << '\n';
  }

  void Render(SDL_Surface* surface) override {
    std::cout
      << " - Rendering at x = " << xPosition;
    // ...
  }
};