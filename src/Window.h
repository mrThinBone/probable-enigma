#pragma once
#include <SDL3/SDL.h>
#include <iostream>

class Window {
public:
  Window() {
    sdlWindow = SDL_CreateWindow(
      "Hello Window",
      800, 300, 0
    );
    
    SDL_GetWindowSurface(sdlWindow);
  }

  // don't need our Window objects to be copyable
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  ~Window() {
    if (sdlWindow && SDL_WasInit(SDL_INIT_VIDEO)) {
      SDL_DestroyWindow(sdlWindow);
    } else {
      std::cout << "Skipping SDL_DestroyWindow\n";
    }
  }

  SDL_Surface* GetSurface() const {
    return SDL_GetWindowSurface(sdlWindow);
  }

  void Render() {
    const auto* fmt = SDL_GetPixelFormatDetails(
      GetSurface()->format
    );
    SDL_FillSurfaceRect(
      GetSurface(),
      nullptr,
      SDL_MapRGB(fmt, nullptr, 50, 50, 50)
    );
  }

  void Update() {
    SDL_UpdateWindowSurface(sdlWindow);
  }
  
private:
  SDL_Window* sdlWindow{nullptr};
};