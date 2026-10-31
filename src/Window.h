#pragma once
#include <SDL3/SDL.h>
#include <iostream>

class Window {
public:
  Window() {
    SDLWindow = SDL_CreateWindow(
      "Hello Window",
      800, 300, 0
    );
    
    SDL_GetWindowSurface(SDLWindow);
  }

  // don't need our Window objects to be copyable
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  ~Window() {
    if (SDLWindow && SDL_WasInit(SDL_INIT_VIDEO)) {
      SDL_DestroyWindow(SDLWindow);
    } else {
      std::cout << "Skipping SDL_DestroyWindow\n";
    }
  }

  SDL_Surface* GetSurface() const {
    return SDL_GetWindowSurface(SDLWindow);
  }

  void Render() {
    const auto* Fmt = SDL_GetPixelFormatDetails(
      GetSurface()->format
    );
    SDL_FillSurfaceRect(
      GetSurface(),
      nullptr,
      SDL_MapRGB(Fmt, nullptr, 50, 50, 50)
    );
  }

  void Update() {
    SDL_UpdateWindowSurface(SDLWindow);
  }
  
private:
  SDL_Window* SDLWindow{nullptr};
};