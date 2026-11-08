#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "../Globals.h"

namespace Engine{
  class Image {
  public:
    Image(
      int x, int y, int w, int h,
      const std::string& Filename,
      int Padding = 12
    ): destination{
      x + Padding/2, y + Padding/2,
      w-Padding, h-Padding
    }{
      imageSurface = IMG_Load(Filename.c_str());
#ifdef SHOW_DEBUG_HELPERS
      Utils::CheckSDLError("IMG_Load");
#endif
    }

    void Render(SDL_Surface* Surface) {
      SDL_BlitSurfaceScaled(
        imageSurface, nullptr,
        Surface, &destination,
        SDL_SCALEMODE_LINEAR
      );
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