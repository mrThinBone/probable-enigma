#pragma once
#include <SDL3/SDL.h>
#include "Engine/Vec2.h"
#include "Engine/Image.h"
#include "Scene.h"
#include "Config.h"

class Scene;

class GameObject {
public:
  GameObject(
    const std::string& imagePath,
    const Vec2& initialPosition,
    const Scene& scene ) : image{imagePath},
                           position{initialPosition},
                           scene{scene} {}

  void HandleEvent(SDL_Event& event) {}
  void Tick(float deltaTime) {}
  void Render(SDL_Surface* surface);
  Vec2 position;
  
  float time{0};

  // 100 pixels/sec right
  //Vec2 velocity{2.0f * PIXELS_PER_METER, 0.0f};
  Vec2 direction{1, 0};
  float MaximumSpeed{2.0f * PIXELS_PER_METER};

  // Accelerate 1m/s^2 (50 pixels/s^2) to the left
  Vec2 acceleration{-1.0f * PIXELS_PER_METER, 0.0f};

private:
  Engine::Image image;
  const Scene& scene;
};