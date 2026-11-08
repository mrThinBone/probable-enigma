#pragma once
#include <SDL3/SDL.h>

namespace Engine{
  class Rectangle {
  public:
    Rectangle(
      int x, int y, int w, int h,
      SDL_Color color = {0, 0, 0, 255})
      : rect{x, y, w, h}, color{color}{}

    virtual void Render(SDL_Surface* Surface){
      const auto* fmt = SDL_GetPixelFormatDetails(
        Surface->format
      );
      SDL_FillSurfaceRect(
        Surface, &rect, SDL_MapRGB(
          fmt, nullptr, color.r, color.g, color.b
        )
      );
    }

    void SetColor(SDL_Color C){ color = C; }

    bool IsWithinBounds(int x, int y) const{
      if (x < rect.x) return false;
      if (x > rect.x + rect.w) return false;
      if (y < rect.y) return false;
      if (y > rect.y + rect.h) return false;
      return true;
    }

    const SDL_Rect* GetRect() const { return &rect; }

    virtual ~Rectangle() = default;

  private:
    SDL_Rect rect{0, 0, 0, 0};
    SDL_Color color{0, 0, 0, 0};
  };
}