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
}