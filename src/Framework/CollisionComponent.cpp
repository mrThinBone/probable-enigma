#include <iostream>
#include <cmath>
#include "CollisionComponent.h"
#include "Entity.h"
#include "Utilities.h"
#include "Scene.h"

void CollisionComponent::Tick(float DeltaTime) {
  Vec2 ownerPos{GetOwnerPosition()};
  float ownerScale{GetOwnerScale()};

  // Calculate position and dimensions
  bounds.x = ownerPos.x + offset.x;
  bounds.y = ownerPos.y + offset.y;
  bounds.w = width * ownerScale;
  bounds.h = height * ownerScale;
}

void CollisionComponent::Initialize() {
  if (!GetOwner()->GetTransformComponent()) {
    std::cerr << "Error: CollisionComponent "
      "requires TransformComponent on its Owner.\n";
    GetOwner()->RemoveComponent(this);
  }
}

void CollisionComponent::SetOffset(const Vec2& newOffset) {
  offset = newOffset;
}

void CollisionComponent::SetSize(float newWidth, float newHeight) {
  if (newWidth < 0 || newHeight < 0) {
    std::cerr << "Warning: CollisionComponent "
      "width/height cannot be negative. "
      "Using absolute values.\n";
    width = std::abs(newWidth);
    height = std::abs(newHeight);
  } else {
    width = newWidth;
    height = newHeight;
  }
}

const SDL_FRect& CollisionComponent::GetBounds() const {
  return bounds;
}

bool CollisionComponent::IsCollidingWith(const CollisionComponent& other) const {
  return SDL_HasRectIntersectionFloat(
    &bounds, &other.bounds
  );
}

void CollisionComponent::DrawDebugHelpers(SDL_Surface* surface) {
  // Convert bounds to integer SDL_Rect for drawing
  SDL_Rect screenBounds{Utilities::Round(bounds)};

  // Draw outline using the helper
  Utilities::DrawRectOutline(
    surface,
    screenBounds,
    // Yellow
    SDL_MapRGB(
      SDL_GetPixelFormatDetails(surface->format),
      nullptr, 255, 255, 0
    ),
    1 // Thin line
  );
}

bool CollisionComponent::GetCollisionRectangle(
  const CollisionComponent& other,
  SDL_FRect* outIntersection
) const {
  // Ensure the output pointer is valid
  if (!outIntersection) {
    std::cerr << "Error: outIntersection pointer "
      "is null in GetCollisionRectangle.\n";
    return false;
  }

  return SDL_GetRectIntersectionFloat(
    &bounds, &other.bounds, outIntersection);
}