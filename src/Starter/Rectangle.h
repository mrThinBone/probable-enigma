#pragma once
#include <SDL3/SDL.h>
#include <iostream>

class Rectangle {
private:
  SDL_Rect rect;
  
  SDL_Color color{255, 0, 0};

  bool isPointerHovering{false};
  SDL_Color hoverColor{0};

  /*bool isWithinRect(int x, int y) {
    // Too far left
    if (x < rect.x) return false;
    // Too far right
    if (x > rect.x + rect.w) return false;
    // Too far up
    if (y < rect.y) return false;
    // Too far down
    if (y > rect.y + rect.h) return false;

    // If we got this far, that means the
    // point is within the rectangle
    return true;
  }*/
  bool isWithinRect(int x, int y) {
    SDL_Point mousePosition{ x, y };
    return SDL_PointInRect(&mousePosition, &rect);
  }

public:
  Rectangle(
    const SDL_Rect& rect
    //const SDL_PixelFormatDetails* Fmt
  )
  : rect{rect},
    // Default to red
    color{SDL_Color {255, 0, 0, 255}}
  {}

  virtual ~Rectangle() = default;

  virtual void Render(SDL_Surface* surface) const {
    auto [r, g, b, a]{
      isPointerHovering ? hoverColor : color
    };

    const auto* Fmt = SDL_GetPixelFormatDetails(
      surface->format
    );

    SDL_FillSurfaceRect(
      surface,
      &rect, 
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

  void SetColor(const SDL_Color& newColor) {
    color = newColor;
  }

  void SetHoverColor(const SDL_Color& newColor) {
    hoverColor = newColor;
  }

  SDL_Color GetHoverColor() const {
    return hoverColor;
  }
};