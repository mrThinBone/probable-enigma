#pragma once
#include <SDL3/SDL.h>
#include "../Globals.h"

namespace Engine{
class Window {
public:
  Window(){
    sdlWindow = SDL_CreateWindow(
      Config::GAME_NAME.c_str(),
      Config::WINDOW_WIDTH,
      Config::WINDOW_HEIGHT,
      0
    );
  }

  void Render(){
    const auto* Fmt = SDL_GetPixelFormatDetails(GetSurface()->format);
    SDL_FillSurfaceRect(
      GetSurface(), nullptr,
      SDL_MapRGB(Fmt, nullptr,
        Config::BACKGROUND_COLOR.r,
        Config::BACKGROUND_COLOR.g,
        Config::BACKGROUND_COLOR.b)
    );
  }

  void Update(){
    SDL_UpdateWindowSurface(sdlWindow);
  }

  SDL_Surface* GetSurface() const {
    return SDL_GetWindowSurface(sdlWindow);
  }

  ~Window() {
    if (sdlWindow && SDL_WasInit(SDL_INIT_VIDEO)) {
      SDL_DestroyWindow(sdlWindow);
    }
  }

  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

private:
  SDL_Window* sdlWindow{nullptr};
};
}