#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "Framework/Entity.h"
#include "Framework/Context.h"
#include "Character.h"


using EntityPtr = std::unique_ptr<Entity>;
using EntityPtrs = std::vector<EntityPtr>;

class Scene {
public:
  explicit Scene(Context& context) : context{context} {
    // Create a Character instead of a generic Entity
    // The Character constructor handles adding
    // its default components
    entities.emplace_back(
      std::make_unique<Character>(context)
    );
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

    CheckCollisions();
  }

  void Render(SDL_Surface* surface) {
    for (EntityPtr& entity : entities) {
      entity->Render(surface);
    }
#ifdef DRAW_DEBUG_HELPERS
    SDL_BlitSurface(
      trajectories, nullptr, surface, nullptr
    );
#endif
  }

#ifdef DRAW_DEBUG_HELPERS
  SDL_Surface* trajectories{
    SDL_CreateSurface(
      700, 300,
      SDL_PIXELFORMAT_RGBA32
    )
  };
#endif

private:
  Context& context;
  EntityPtrs entities;

  void CheckCollisions();
};