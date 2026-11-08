#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Goblin.h"

class World {
 public:
  void HandleEvent(const SDL_Event& E) {
    for (auto& object : gameObjects) {
      object->HandleEvent(E);
    }
  }

  void Tick(float timeDelta) {
    for (auto& object : gameObjects) {
      object->Tick(timeDelta);
    }
  }

  void Render(SDL_Surface* Surface) {
    for (auto& object : gameObjects) {
      object->Render(Surface);
    }
  }

  Goblin& SpawnGoblin(const std::string& name, int x, int y) 
  {
    gameObjects.emplace_back(
      std::make_unique<Goblin>(name, x, y)
    );
    return static_cast<Goblin&>(*gameObjects.back());
  }

  template <typename T, typename... Args> T& SpawnObject(Args&&... args) {
    gameObjects.emplace_back(
      std::make_unique<T>(std::forward<Args>(args)...)
    );

    return static_cast<T&>(*gameObjects.back());
  }

  void AddObject(std::unique_ptr<GameObject> object) {
    gameObjects.emplace_back(std::move(object));
  }

 private:
  std::vector<std::unique_ptr<GameObject>> gameObjects;
};