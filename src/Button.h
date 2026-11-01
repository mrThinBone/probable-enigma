#pragma once
#include <SDL3/SDL.h>
#include "Rectangle.h"

class Button : public Rectangle {
 public:
  Button(const SDL_Rect& Rect)
  : Rectangle{Rect}
  {
    SetColor({255, 165, 0, 255}); // Orange 
  }

  void HandleEvent(SDL_Event& E) {
    Rectangle::HandleEvent(E); 
    // Implement button-specific event logic...
  }

  void Render(SDL_Surface* Surface) const override {
    Rectangle::Render(Surface); 
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