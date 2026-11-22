#pragma once
#include <SDL3/SDL.h>

// Forward declaration to avoid circular includes
class Entity;
class AssetManager;
class Scene;

class Component {
public:
  // Constructor now takes a pointer to the
  // owning Entity
  Component(Entity* owner) : owner(owner) {} 

  virtual void Initialize() {}
  virtual void HandleEvent(const SDL_Event& E) {}
  virtual void Tick(float deltaTime) {}
  virtual void Render(SDL_Surface* surface) {}
  virtual ~Component() = default;

  AssetManager& GetAssetManager() const;

  virtual void OnComponentRemoved(Component* c) {}

  // Getter for the owning entity
  Entity* GetOwner() const { 
    return owner;
  }

private:
  // Store a pointer to the owner
  Entity* owner{nullptr};
};