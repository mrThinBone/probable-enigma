#pragma once
#include "Component.h"
#include "Vec2.h"
#include <SDL3/SDL.h>

class CollisionComponent : public Component {
 public:
  // Inherit constructor
  using Component::Component;

  // Setters for defining the collision shape
  void SetOffset(const Vec2& newOffset);
  void SetSize(float newWidth, float newHeight);

  // Getter for the calculated bounds
  const SDL_FRect& GetBounds() const;

  // Check collision with another component
  bool IsCollidingWith(
    const CollisionComponent& other
  ) const;

  bool GetCollisionRectangle(
    const CollisionComponent& other,
    SDL_FRect* outIntersection
  ) const;

  // Called each frame to update Bounds
  void Tick(float deltaTime) override;
  // Dependency check
  void Initialize() override;
  // Draw the bounding box
  void DrawDebugHelpers(SDL_Surface*) override;

 private:
  // Shape definition relative to owner's origin
  Vec2 offset{0.0, 0.0};
  float width{1.0};  // Default 1x1
  float height{1.0};

  // Calculated bounds updated each tick
  SDL_FRect bounds{0.0, 0.0, 0.0, 0.0};
};