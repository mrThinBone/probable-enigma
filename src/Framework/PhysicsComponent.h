#pragma once
#include "Component.h"
#include "Vec2.h"

class PhysicsComponent : public Component {
 public:
  using Component::Component;
  PhysicsComponent(Entity* owner, const Vec2& gravity);
  void Initialize() override;

  void Tick(float deltaTime) override;
  void DrawDebugHelpers(SDL_Surface* trajectories) override;

  void ApplyForce(const Vec2& force);
  void ApplyImpulse(const Vec2& impulse);

  Vec2 GetVelocity() const { return velocity; }
  void SetVelocity(const Vec2& newVelocity) {
    velocity = newVelocity;
  }

  float GetMass() const { return mass; }
  void SetMass(float newMass);

//   void SetTrajectories(SDL_Surface* surface) { trajectories = surface; }

 private:
  Vec2 velocity{0.0, 0.0}; // m/s
  Vec2 acceleration{0.0, 0.0}; // m/s^2
  float mass{1.0}; // kg

  Vec2 gravity;
//   SDL_Surface* trajectories{nullptr};
};