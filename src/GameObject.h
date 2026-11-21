#pragma once
#include <SDL3/SDL.h>
#include "Engine/Vec2.h"
#include "Engine/Image.h"
#include "Engine/BoundingBox.h"
#include "Scene.h"
#include "Config.h"

class Scene;

class GameObject {
public:
  GameObject(
    const std::string& imagePath,
    const Vec2& initialPosition,
    const Scene& scene,
    float width,
    float height
  ) :                     image{imagePath},
                          position{initialPosition},
                          scene{scene},
                          bounds{ SDL_FRect{
                            initialPosition.x, initialPosition.y,
                            width, height
                          } } {}

  void HandleEvent(SDL_Event& event) {}
  void Tick(float deltaTime) {}
  void Render(SDL_Surface* surface);
  void ApplyForce(const Vec2& force);
  Vec2 position;
  
  float time{0};

  // 100 pixels/sec right
  
  // Vec2 direction{1, 0};
  // float MaximumSpeed{2.0f * PIXELS_PER_METER};

  // Accelerate 1m/s^2 (50 pixels/s^2) to the left
  // -1.0f * PIXELS_PER_METER, 0.0f
  Vec2 acceleration{0.0f, 0.0f};

  Vec2 GetFrictionForce(float deltaTime) const {
    // How much force can friction apply
    float maxMagnitude{GetFrictionCoefficient()
      * mass * acceleration.y};

    // There is no friction
    if (maxMagnitude <= 0) return Vec2{0, 0};

    // How much force is required to stop the
    // object right now
    float stoppingMagnitude{mass * 
      velocity.GetLength() / deltaTime};

    // Return the smaller of the two forces
    return -velocity.Normalize() * std::min(
      maxMagnitude, stoppingMagnitude);
  }

private:
  Engine::Image image;
  const Scene& scene;
  BoundingBox bounds;
  float mass{50.0f};
  
  float forceTimeRemaining{5.0f};

  void Clamp(Vec2& v) const {
    v.x = std::abs(v.x) > 0.1f ? v.x : 0.0f;
    v.y = std::abs(v.y) > 0.1f ? v.y : 0.0f;
  }

  // https://www.studyplan.dev/sdl3/sdl3-force-drag-friction
  
  Vec2 velocity{2.0f * PIXELS_PER_METER, 0.0f};
  
  float dragCoefficient{0.2f};
  
  Vec2 GetDragForce() {
    return -velocity * velocity.GetLength()
      * dragCoefficient;
  }
  

  //float frictionCoefficient{0.5f};
  float GetFrictionCoefficient() const {
    // Assuming a vertical position < 200 means
    // the object is in the air (Y increases downwards)
    if (position.y < 200) {
      // Object isn't on the ground
      return 0;
    }

    if (position.x > 250 && position.x < 300) {
      // Area from x=250 to x=300 is icy
      return 0.1f;
    }

    // Default friction amount
    return 0.5f;
  }
  
  void ApplyImpulse(const Vec2& impulse) {
    velocity += impulse / mass;
  }

  void ApplyPositionalImpulse(const Vec2& origin, float magnitude) {
    Vec2 direction{(position - origin).Normalize()};
    ApplyImpulse(direction * magnitude);
  }
};