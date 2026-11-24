#pragma once
#include <iostream>
#include <SDL3/SDL.h>

class Window {
public:
  Window() {
    SDLWindow = SDL_CreateWindow(
      "Scene",
      700, 300, 0
    );
  }

  ~Window() {
    if (SDLWindow) {
      SDL_DestroyWindow(SDLWindow);
    }
  }

  // Prevent copying
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  void Render() {
    // Clear background to dark gray
    const auto* Fmt{SDL_GetPixelFormatDetails(
      GetSurface()->format
    )};
    SDL_FillSurfaceRect(
      GetSurface(),
      nullptr,
      SDL_MapRGB(Fmt, nullptr, 30, 30, 30)
    );
  }

  void Update() {
    SDL_UpdateWindowSurface(SDLWindow);
  }

  SDL_Surface* GetSurface() {
    return SDL_GetWindowSurface(SDLWindow);
  }

private:
  SDL_Window* SDLWindow;
};