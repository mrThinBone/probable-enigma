#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>

class Triangle {
public:
  Triangle() {
    // Define vertices in Local Space
    // (Relative to the center of the triangle)
    vertices = {
      {0.0f, -0.577f, 0.0f},  // Bottom
      {0.5f, 0.289f, 0.0f},   // Top Right
      {-0.5f, 0.289f, 0.0f}   // Top Left
    };
  }

  void HandleEvent(SDL_Event& Event) {
    if (Event.type == SDL_EVENT_KEY_DOWN) {
      switch (Event.key.key) {
        case SDLK_LEFT: position.x -= 0.1f; break;
        case SDLK_RIGHT: position.x += 0.1f; break;
        case SDLK_UP: position.y += 0.1f; break;
        case SDLK_DOWN: position.y -= 0.1f; break;
        case SDLK_PLUS: scale += 0.1f; break;
        case SDLK_MINUS: scale -= 0.1f; break;
        default: break;
      }
    } else if (Event.type == SDL_EVENT_MOUSE_WHEEL) {
      if (Event.wheel.y > 0) scale += 0.1f;
      if (Event.wheel.y < 0) scale -= 0.1f;
    }
  }
  void Tick(float DeltaTime) {
    rotation += 90.0f * DeltaTime;
  }
  void Render(SDL_Surface* surface) {
    // Create our transformation as an identity matrix
    glm::mat4 model{1.0f}; 

    // always follow The order of operations: Translate -> Rotate -> Scale
    model = glm::translate(model, position); 
    model = glm::rotate(
      model,
      glm::radians(rotation),
      glm::vec3{0.0f, 0.0f, 1.0f}
    );
    // model = glm::scale(model, glm::vec3{3.0f, 1.0f, 1.0f}); // scale X only
    model = glm::scale(model, glm::vec3{ scale });

    for (const glm::vec3& localVertex : vertices) {
      // Implement the transformation
      glm::vec4 worldVertex{
        // - matrix on the left, vertex on the right
        // - vertex is updated to a vec4, with w=1
        model * glm::vec4{localVertex, 1.0f}
      };

      DrawVertex(surface, worldVertex);
    }
  }

private:
  std::vector<glm::vec3> vertices;
  glm::vec3 position{0.0f, 0.0f, 0.0f}; 
  float scale{1.0f};
  float rotation{90.0f}; // Degrees 
  

  void DrawVertex(
    SDL_Surface* surface, const glm::vec3& vertex
  ) {

    // Position
    float ScreenW{float(Surface->w)};
    float ScreenH{float(Surface->h)};
    float ScreenX{(vertex.x * 100.0f) + (ScreenW * 0.5f)};
    float ScreenY{(vertex.y * -100.0f) + (ScreenH * 0.5f)};

    // Color
    const auto* fmt{
      SDL_GetPixelFormatDetails(surface->format)
    };
    Uint32 Color{SDL_MapRGB(fmt, nullptr, 255, 0, 0)};

    // Draw
    SDL_Rect pixelRect{
      int(ScreenX) - 5,
      int(ScreenY) - 5,
      10, 10
    };
    SDL_FillSurfaceRect(Surface, &pixelRect, Color);
  }
};