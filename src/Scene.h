#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "GameObject.h"

class Scene {
public:
  Scene() {
    objects.emplace_back(
      "dwarf.png", Vec2{100, 200}, *this
    );
  }

  void HandleEvent(SDL_Event& E) {
    for (GameObject& object : objects) {
      object.HandleEvent(E);
    }
  }

  void Tick(float deltaTime) {
    for (GameObject& object : objects) {
      object.ApplyForce({5.0f * PIXELS_PER_METER, 0});
      object.Tick(deltaTime);
    }
  }

  void Render(SDL_Surface* surface) {
    for (GameObject& object : objects) {
      object.Render(surface);
    }
  }

private:
  std::vector<GameObject> objects;
};