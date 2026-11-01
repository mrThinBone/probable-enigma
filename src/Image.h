#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <string>

class Image {
public:
  Image(
    const std::string& file,
    SDL_PixelFormat preferredFormat = SDL_PIXELFORMAT_UNKNOWN
  ) : imageSurface{SDL_LoadBMP(file.c_str())} {
    if (!imageSurface) {
      std::cout << "Failed to load image: "
        << file << ":\n  " << SDL_GetError() << '\n';
    } else if (preferredFormat != SDL_PIXELFORMAT_UNKNOWN) {
      SDL_Surface* converted{
        SDL_ConvertSurface(imageSurface, preferredFormat)
      };
      if (converted) {
        SDL_DestroySurface(imageSurface);
        imageSurface = converted;
        SDL_SetSurfaceBlendMode(imageSurface, SDL_BLENDMODE_NONE);
      } else {
        std::cout << "Error converting surface: "
          << SDL_GetError() << '\n';
      }
    }
  }

  void Render(SDL_Surface* destinationSurface) {
    if (!imageSurface) return;
    if (destinationSurface->format == 
        imageSurface->format
    ) {
      std::cout << "Matched Format Blit\n";
    } else {
      std::cout << "Reformat Required\n";
    }
    SDL_BlitSurface(
      imageSurface, nullptr,
      destinationSurface, nullptr
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
};