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

      // Initialize SourceRectangle to the full image size
      sourceRectangle = {
        0, 0, imageSurface->w, imageSurface->h
      };

      
      SDL_Surface* converted{ SDL_ConvertSurface(imageSurface, preferredFormat) };
      
      if (converted) {
        SDL_DestroySurface(imageSurface);
        imageSurface = converted;
        // huge perf different
        SDL_SetSurfaceBlendMode(imageSurface, SDL_BLENDMODE_NONE);
      } else {
        std::cout << "Error converting surface: "
          << SDL_GetError() << '\n';
      }
    }
  }

  ~Image() {
    if (imageSurface) {
      SDL_DestroySurface(imageSurface);
    }
  }

  Image(const Image&) = delete;
  Image& operator=(const Image&) = delete;

  void Render(SDL_Surface* destinationSurface) {
    if (!imageSurface) return;
#ifdef DEBUG_LOGGING
    if (destinationSurface->format == imageSurface->format) 
    {
      std::cout << "Matched Format Blit\n";
    } 
    else 
    {
      std::cout << "Reformat Required\n";
    }
#endif

    if (scaleToFit)
    {
      destinationRectangle.w = destinationSurface->w;
      destinationRectangle.h = destinationSurface->h;
    }
    else
    { // maintain image ratio
      float originalRatio{sourceRectangle.w / static_cast<float>(sourceRectangle.h)};

      float targetRatio{destinationSurface->w / static_cast<float>(destinationSurface->h)};

      if (targetRatio < originalRatio)
      {
        // Reduce height
        destinationRectangle.h = static_cast<int>(
            destinationSurface->w / originalRatio);
      }
      else
      {
        // Reduce width as before
        destinationRectangle.w = static_cast<int>(
            destinationSurface->h * originalRatio);
      }
    }

    SDL_BlitSurfaceScaled(
      imageSurface, &sourceRectangle,
      destinationSurface, &destinationRectangle,
      SDL_SCALEMODE_LINEAR
    );
#ifdef DEBUG_LOGGING
    // Manually check for clipping
    SDL_Rect intendedDestRect{
      destinationRectangle.x, destinationRectangle.y,
      sourceRectangle.w, sourceRectangle.h
    };

    SDL_Rect destBounds{
      0, 0, destinationSurface->w, destinationSurface->h
    };

    SDL_Rect clippedRect; // visible zone
    SDL_GetRectIntersection(
      &intendedDestRect, &destBounds, &clippedRect
    );

    if (clippedRect.w != sourceRectangle.w) {
      std::cout << "Clipping Horizontally\n";
    }
    if (clippedRect.h != sourceRectangle.h) {
      std::cout << "Clipping Vertically\n";
    }
#endif
  }

  SDL_Point GetSize() const {
    return {imageSurface->w, imageSurface->h};
  }

  void Crop(int x, int y, int w, int h) {
    sourceRectangle.x = x;
    sourceRectangle.y = y;
    sourceRectangle.w = w;
    sourceRectangle.h = h;
  }

  void Move(int x, int y) {
    destinationRectangle.x = x;
    destinationRectangle.y = y;
  }

  void ScaleToFit(bool scale) {
    scaleToFit = scale;
  }

private:
  SDL_Surface* imageSurface{nullptr};
  SDL_Rect sourceRectangle{};
  // with SDL_BlitSurfaceScaled, width & height of destination rectangle are no longer ignored
  SDL_Rect destinationRectangle{0, 0, 0, 0};
  bool scaleToFit = false;
};