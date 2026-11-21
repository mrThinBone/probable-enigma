#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Globals.h"
#include "Vec2.h"

namespace Engine{
  class Image {
  public:
    Image(
      int x, int y, int w, int h,
      const std::string& filename,
      int padding = 12
    ): destination{ x + padding/2, y + padding/2, w-padding, h-padding }
    {

      imageSurface = IMG_Load(filename.c_str());

#ifdef SHOW_DEBUG_HELPERS
      Utils::CheckSDLError("IMG_Load");
#endif
    }

    Image(const std::string& path) {

      imageSurface = IMG_Load(path.c_str());

#ifdef SHOW_DEBUG_HELPERS
      Utils::CheckSDLError("IMG_Load");
#endif
    }

    void Render(SDL_Surface* surface) {
      SDL_BlitSurfaceScaled(
        imageSurface, nullptr, surface, 
        &destination, SDL_SCALEMODE_LINEAR
      );
    }

    void Render(SDL_Surface* surface, SDL_Rect* rect) {
      SDL_BlitSurfaceScaled(
        imageSurface, nullptr, surface, 
        rect, SDL_SCALEMODE_LINEAR
      );
    }

    void Render(SDL_Surface* surface, const Vec2& pos) {
      if (imageSurface) {
        SDL_Rect rect{
          int(pos.x), int(pos.y),
          imageSurface->w, imageSurface->h
        };
        SDL_BlitSurface(
          imageSurface, nullptr, surface, &rect);
      }
    }


    ~Image() {
      if (imageSurface) {
        SDL_DestroySurface(imageSurface);
      }
    }

    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

  private:
    SDL_Surface* imageSurface{nullptr};
    SDL_Rect destination{0, 0, 0, 0};
  };
}