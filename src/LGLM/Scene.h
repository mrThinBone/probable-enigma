#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include "Triangle.h" 

class Scene {
public:
  Scene() {
    // Add a single triangle to the scene
    Triangles.emplace_back(); 
  }
  
  void HandleEvent(SDL_Event& Event) {
    for (auto& Tri : Triangles) { 
      Tri.HandleEvent(Event); 
    } 
  }

  void Tick(float DeltaTime) {
    for (auto& Tri : Triangles) { 
      Tri.Tick(DeltaTime); 
    } 
  }

  void Render(SDL_Surface* Surface) {
    for (auto& Tri : Triangles) { 
      Tri.Render(Surface); 
    } 
  }

private:
  std::vector<Triangle> Triangles; 
};