#include <iostream>
#include "PhysicsComponent.h"
#include "Entity.h"
#include "Scene.h"

PhysicsComponent::PhysicsComponent(Entity* owner, const Vec2& gravity) : Component(owner), gravity(gravity) {}

void PhysicsComponent::Initialize() {
  if (!GetOwner()->GetTransformComponent()) {
    std::cerr << "Error: PhysicsComponent "
      "requires TransformComponent on its Owner.\n";

    GetOwner()->RemoveComponent(this);
  }
}

void PhysicsComponent::SetMass(float newMass) {
  if (newMass <= 0.0) {
    std::cerr << "Error: Mass must be positive. "
                 "Setting to 1.0kg instead.\n";
    mass = 1.0;
  } else {
    mass = newMass;
  }
}

void PhysicsComponent::ApplyForce(const Vec2& force) {
  if (mass > 0.0f) {
    acceleration += force / mass;
  }
}

void PhysicsComponent::ApplyImpulse(const Vec2& impulse) {
  if (mass > 0.0f) {
    velocity += impulse / mass;
  }
}

void PhysicsComponent::Tick(float deltaTime) {
  ApplyForce(gravity * mass);

  velocity += acceleration * deltaTime;
  SetOwnerPosition(
    GetOwnerPosition() + velocity * deltaTime
  );
  acceleration = {0.0, 0.0};
}

void PhysicsComponent::DrawDebugHelpers(
  SDL_Surface* trajectories
) {
#ifdef DRAW_DEBUG_HELPERS
  if (!trajectories) return;

  auto [x, y]{GetOwnerPosition()};

  SDL_Rect positionIndicator{ int(x) - 2, int(y) - 2, 4, 4 };
  
  SDL_FillSurfaceRect(
    trajectories,
    &positionIndicator,
    SDL_MapRGB(
      SDL_GetPixelFormatDetails(
        trajectories->format
      ),
      nullptr, 0, 0, 255
    )
  );
#endif
}