#pragma once
#include <SDL3/SDL.h>

class Rectangle {
private:
  SDL_Rect Rect;
  
  Uint32 Color{0};

  bool isPointerHovering{false};
  Uint32 HoverColor{0};

  bool isWithinRect(int x, int y) {
    // Too far left
    if (x < Rect.x) return false;
    // Too far right
    if (x > Rect.x + Rect.w) return false;
    // Too far up
    if (y < Rect.y) return false;
    // Too far down
    if (y > Rect.y + Rect.h) return false;

    // If we got this far, that means the
    // point is within the rectangle
    return true;
  }

public:
  Rectangle(
    const SDL_Rect& Rect,
    const SDL_PixelFormatDetails* Fmt
  )
  : Rect{Rect},
    // Default to red
    Color{SDL_MapRGB(Fmt, nullptr, 255, 0, 0)}
  {}

  void Render(SDL_Surface* Surface) const {
    Uint32 color = isPointerHovering ? HoverColor : Color;

    const auto* Fmt = SDL_GetPixelFormatDetails(
      Surface->format
    );

    SDL_FillSurfaceRect(
      Surface,
      &Rect, 
      color
    );
  }

  void HandleEvent(SDL_Event& E) {
    if (E.type == SDL_EVENT_MOUSE_MOTION) {
      // isPointerHovering = isWithinRect(
        // (int)E.motion.x, (int)E.motion.y
      // );
      SDL_Point MousePosition{ (int)E.motion.x, (int)E.motion.y };
      isPointerHovering = SDL_PointInRect(&MousePosition, &Rect);
    } else if (E.type == SDL_EVENT_WINDOW_MOUSE_LEAVE) {
      isPointerHovering = false;
    } else if (E.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      if (isPointerHovering&& E.button.button == SDL_BUTTON_LEFT) {
        std::cout << "A left-click happened "
          "somewhere in the window\n";
      }
    }
  }

  void SetColor(Uint32 NewColor) {
    Color = NewColor;
  }

  void SetHoverColor(Uint32 NewColor) {
    HoverColor = NewColor;
  }

  Uint32 GetHoverColor() const {
    return HoverColor;
  }
};