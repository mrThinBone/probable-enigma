#pragma once
#include <SDL3/SDL.h>
#include <cmath>

namespace Utilities{
  inline SDL_Rect Round(const SDL_FRect& R) {
    return {
      static_cast<int>(std::round(R.x)),
      static_cast<int>(std::round(R.y)),
      static_cast<int>(std::round(R.w)),
      static_cast<int>(std::round(R.h)),
    };
  }

  inline void DrawRectOutline(
    SDL_Surface* surface,
    const SDL_Rect& rect,
    Uint32 color,
    int thickness = 3
  ) {
    SDL_Rect Top{
      rect.x, rect.y, rect.w, thickness
    };
    SDL_FillSurfaceRect(surface, &Top, color);

    SDL_Rect Bottom{
      rect.x,
      rect.y + rect.h - thickness,
      rect.w, thickness
    };
    SDL_FillSurfaceRect(surface, &Bottom, color);

    int sideHeight{rect.h - 2 * thickness};
    SDL_Rect left{
      rect.x,
      rect.y + thickness,
      thickness,
      sideHeight
    };
    SDL_FillSurfaceRect(surface, &left, color);

    SDL_Rect right{
      rect.x + rect.w - thickness,
      rect.y + thickness, thickness,
      sideHeight
    };
    SDL_FillSurfaceRect(surface, &right, color);
  }
}