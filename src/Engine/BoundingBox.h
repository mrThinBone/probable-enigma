#pragma once
#include <SDL3/SDL.h>
#include "Vec2.h"

class BoundingBox {
public:
  BoundingBox(const SDL_FRect& initialRect)
  : rect{initialRect} {}

  void SetPosition(const Vec2& position) {
    rect.x = position.x;
    rect.y = position.y;
  }

  static SDL_Rect Round(const SDL_FRect& rect) {
    return {
      static_cast<int>(std::round(rect.x)),
      static_cast<int>(std::round(rect.y)),
      static_cast<int>(std::round(rect.w)),
      static_cast<int>(std::round(rect.h))
    };
  }

  void Render(SDL_Surface* surface) {
    // Get pixel format details for color mapping
    const auto* fmt{SDL_GetPixelFormatDetails(
      surface->format
    )};

    Uint32 lineColor{SDL_MapRGB(
      fmt, nullptr, 220, 0, 0)};

    SDL_Rect rounded{Round(rect)};
    auto [x, y, w, h]{rounded};

    int lineWidth{4};

    SDL_Rect top{x, y, w, lineWidth};
    SDL_Rect left{x, y, lineWidth, h};
    SDL_Rect bottom{x, y + h - lineWidth, w, lineWidth};
    SDL_Rect right{x + w - lineWidth, y, lineWidth, h};

    SDL_FillSurfaceRect(surface, &top, lineColor);
    SDL_FillSurfaceRect(surface, &left, lineColor);
    SDL_FillSurfaceRect(surface, &bottom, lineColor);
    SDL_FillSurfaceRect(surface, &right, lineColor);
  }

private:
  SDL_FRect rect;
};