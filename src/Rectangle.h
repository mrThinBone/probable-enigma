#pragma once
#include <SDL3/SDL.h>
#include <iostream>

class Rectangle {
private:
  SDL_Rect Rect;
  
  SDL_Color Color{255, 0, 0};

  bool isPointerHovering{false};
  SDL_Color HoverColor{0};

  /*bool isWithinRect(int x, int y) {
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
  }*/
  bool isWithinRect(int x, int y) {
    SDL_Point MousePosition{ x, y };
    return SDL_PointInRect(&MousePosition, &Rect);
  }

public:
  Rectangle(
    const SDL_Rect& Rect
    //const SDL_PixelFormatDetails* Fmt
  )
  : Rect{Rect},
    // Default to red
    Color{SDL_Color {255, 0, 0, 255}}
  {}

  virtual ~Rectangle() = default;

  virtual void Render(SDL_Surface* Surface) const {
    auto [r, g, b, a]{
      isPointerHovering ? HoverColor : Color
    };

    const auto* Fmt = SDL_GetPixelFormatDetails(
      Surface->format
    );

    SDL_FillSurfaceRect(
      Surface,
      &Rect, 
      SDL_MapRGBA(Fmt, nullptr, r, g, b, 255)
    );
  }

  virtual void OnMouseEnter() {}
  virtual void OnMouseExit() {}
  virtual void OnLeftClick() {}

  void HandleEvent(SDL_Event& E) {
    if (E.type == SDL_EVENT_MOUSE_MOTION) {
      bool wasPointerHovering{isPointerHovering};
      isPointerHovering = isWithinRect(
        (int)E.motion.x, (int)E.motion.y
      );
      if (!wasPointerHovering && isPointerHovering) 
      {
        OnMouseEnter();
      } 
      else if (wasPointerHovering && !isPointerHovering) 
      {
        OnMouseExit();
      }
    } else if (E.type == SDL_EVENT_WINDOW_MOUSE_LEAVE) {
      isPointerHovering = false;
    } else if (E.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      if (isPointerHovering &&
        E.button.button == SDL_BUTTON_LEFT
      ) {
        std::cout << "A left-click happened on me!\n";
        OnLeftClick();
      }
    }
  }

  void SetColor(const SDL_Color& NewColor) {
    Color = NewColor;
  }

  void SetHoverColor(const SDL_Color& NewColor) {
    HoverColor = NewColor;
  }

  SDL_Color GetHoverColor() const {
    return HoverColor;
  }
};