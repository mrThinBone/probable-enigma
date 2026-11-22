#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include "Utilities.h"
#include "Engine/Vec2.h"
#include "Component.h"

class TransformComponent : public Component {
public:
  // Inherit the constructor from the base class
  using Component::Component;
  // TransformComponent() {
  //   std::cout << "TransformComponent created\n";
  // }

  void Tick(float deltaTime) override {
    std::cout << "TransformComponent ticking\n";
  }

  Vec2 GetPosition() const {
    return position;
  }

  void SetPosition(const Vec2& newPosition) { 
    position = newPosition; 
  } 

  void Move(const Vec2& movement) {
    position += movement;
  }

  void DrawDebugHelpers(SDL_Surface* surface) override {
    auto [x, y] { GetPosition() };
    SDL_Rect square{Utilities::Round({
      x - 10, y - 10, 20, 20
    })};
    SDL_FillSurfaceRect(surface, &square, SDL_MapRGB(
      SDL_GetPixelFormatDetails(surface->format),
      nullptr, 255, 0, 0));
  }

private:
  Vec2 position{0, 0};
};