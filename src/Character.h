#pragma once
#include <iostream>
#include "Framework/Entity.h"
#include "Framework/ImageComponent.h"
#include "Framework/TransformComponent.h"

class Character : public Entity {
 public:
  explicit Character(Context& context) : Entity{context} {
    // Automatically add required components
    // upon construction. The AddComponent
    // methods already handle passing 'this'
    transform = AddTransformComponent();
    image = AddImageComponent("Assets/sample.bmp");
  }

  // Optionally add Character-specific methods here
  void SayHello() const {
    std::cout << "Character says hello!\n";
  }

 private:
  // Optional: store direct pointers for
  // convenience if frequently accessed.
  TransformComponent* transform{nullptr};
  ImageComponent* image{nullptr};
};