#pragma once
#include <iostream>
#include "Vec2.h"
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

  void Move(const Vec2& movement) {
    position += movement;
  }

private:
  Vec2 position{0, 0};
};