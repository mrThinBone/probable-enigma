#pragma once
#include <SDL3/SDL.h>
#include "Globals.h"
#include "Engine/Text.h"

class RestartButton {
public:
  RestartButton(int x, int y, int w, int h)
    : buttonRect{x, y, w, h},
      currentColor{Config::BUTTON_COLOR},
      text{"RESTART", 20},
      textRect{
        x + Config::PADDING * 5,
        y + Config::PADDING * 3,
        0, 0
      }
    {
        text.SetText("RESTART", Config::FONT_COLOR);
    }

  void Render(SDL_Surface* Surface) {
    SDL_FillSurfaceRect(
      Surface, &buttonRect,
      SDL_MapRGB(
        SDL_GetPixelFormatDetails(Surface->format),
        nullptr,
        currentColor.r,
        currentColor.g,
        currentColor.b
      )
    );
    text.Render(Surface, &textRect);
  }

  void HandleEvent(const SDL_Event& E) {
    if (E.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      HandleClick(E.button);
    }
  }

  void HandleClick(const SDL_MouseButtonEvent& E) {
    if (
      E.x >= buttonRect.x &&
      E.x <= buttonRect.x + buttonRect.w &&
      E.y >= buttonRect.y &&
      E.y <= buttonRect.y + buttonRect.h
    ) {
      SDL_Event RestartEvent{
        .type = UserEvents::RESTART_GAME
      };
      SDL_PushEvent(&RestartEvent);
    }
  }

private:
  Engine::Text text;
  SDL_Rect textRect;
  SDL_Rect buttonRect;
  SDL_Color currentColor;
};