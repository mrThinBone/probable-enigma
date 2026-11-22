#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory> // for std::unique_ptr
#include "GameObject.h"
#include "Config.h"


// Adding some type aliases to reduce noise
using GameObjectPtr = std::unique_ptr<GameObject>;
using GameObjects = std::vector<GameObjectPtr>;

class Scene {
public:
  Scene() {
    objects.emplace_back(std::make_unique<Player>(
      "dwarf.png", Vec2{100, 200}, *this,
      1.9f * PIXELS_PER_METER,
      1.7f * PIXELS_PER_METER
    ));

    // objects.emplace_back(
    //   "dragon.png",
    //   Vec2{
    //     30.0f * PIXELS_PER_METER,
    //     1.0f * PIXELS_PER_METER
    //   },
    //   *this,
    //   2.0f * PIXELS_PER_METER,
    //   2.0f * PIXELS_PER_METER
    // );

    objects.emplace_back(std::make_unique<Floor>(
      "floor.png",
      Vec2{
        3.0f * PIXELS_PER_METER,
        5.0f * PIXELS_PER_METER
      },
      2.0f * PIXELS_PER_METER,
      2.0f * PIXELS_PER_METER,
      *this,
      false
    ));
  }

  const GameObject& GetPlayerCharacter() const {
    return objects[0];
  }

  void HandleEvent(SDL_Event& E) {
    for (GameObjectPtr& object : objects) {
      object->HandleEvent(E);
    }
  }

  void Tick(float DeltaTime) {
    for (GameObjectPtr& object : objects) {
      object->Tick(DeltaTime);
    }
  }

  void Render(SDL_Surface* surface) {
    SDL_GetSurfaceClipRect(surface, &viewport);
    for (GameObjectPtr& object : objects) {
      object->Render(surface);
    }
  }

  SDL_Rect GetViewport() const {
    return viewport;
  }

  const GameObjects& GetObjects() const {
    return objects;
  }

private:
//   std::vector<GameObject> objects;
  GameObjects objects;
  SDL_Rect viewport;
};