#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "Framework/Entity.h"
#include "Character.h"

using EntityPtr = std::unique_ptr<Entity>;
using EntityPtrs = std::vector<EntityPtr>;

class Scene {
public:
    Scene() {
    // Create a Character instead of a generic Entity
    // The Character constructor handles adding
    // its default components
    EntityPtr& newCharacter{entities.emplace_back(
      std::make_unique<Character>()
    )};
  }

  void HandleEvent(const SDL_Event& E) {
    for (EntityPtr& entity : entities) {
      entity->HandleEvent(E);
    }
  }

  void Tick(float DeltaTime) {
    for (EntityPtr& entity : entities) {
      entity->Tick(DeltaTime);
    }
  }

  void Render(SDL_Surface* Surface) {
    for (EntityPtr& entity : entities) {
      entity->Render(Surface);
    }
  }

private:
  EntityPtrs entities;
};