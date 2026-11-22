#pragma once
#include <iostream>
#include "Component.h"

class ImageComponent : public Component {
public:
  // Inherit the constructor from the base class
  using Component::Component;

  // ImageComponent() {
  //   std::cout << "ImageComponent created\n";
  // }

  void Initialize() override; 
  void Render(SDL_Surface* surface) override;
};