#pragma once
#include <SDL3/SDL.h>
#include "Rectangle.h"

class Button : public Rectangle {
 public:
  Button(const SDL_Rect& rect): Rectangle{rect}
  {
    SetColor({255, 165, 0, 255}); // Orange 
  }

  void HandleEvent(SDL_Event& e) {
    Rectangle::HandleEvent(e); 
    // Implement button-specific event logic...
  }

  void Render(SDL_Surface* surface) const override {
    Rectangle::Render(surface); 
    // Render the rest of the button...
  }

  void OnMouseEnter() override {
    std::cout << "Hello mouse\n";
  }

  void OnMouseExit() override {
    std::cout << "Goodbye mouse\n";
  }

  void OnLeftClick() override {
    std::cout << "You left-clicked me!\n";
  }
};