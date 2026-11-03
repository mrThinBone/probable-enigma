#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <string>

class Image {
public:
  Image(const std::string& file): imageSurface{IMG_Load(file.c_str())} {
    if (!imageSurface) {
      std::cout << "Failed to load image: "
        << file << ":\n  " << SDL_GetError() << '\n';

      // Initialize SourceRectangle to the full image size
      sourceRectangle = {
        0, 0, imageSurface->w, imageSurface->h
      };

      // blending is enabled by default for SDL_Surface objects, but it's good to explicitly set it anyway
      SDL_SetSurfaceBlendMode(imageSurface, SDL_BLENDMODE_BLEND);
      // disable
      // SDL_SetSurfaceBlendMode(imageSurface, SDL_BLENDMODE_NONE);
    }
  }

  ~Image() {
    if (imageSurface) {
      SDL_DestroySurface(imageSurface);
    }
  }

  // Image(const Image&) = delete;
  Image(const Image& source): destinationRectangle(source.destinationRectangle) {
    // Copy the SDL_Surface using SDL_ConvertSurface
    if (source.imageSurface) {
      imageSurface = SDL_ConvertSurface(
        source.imageSurface,
        source.imageSurface->format
      );
    }
  }
  // Image& operator=(const Image&) = delete;
  Image& operator=(const Image& source) {
    // Early return for self-assignment
    if (this == &source) {
      return *this;
    }

    // Free current resources
    if (imageSurface) {
      SDL_DestroySurface(imageSurface);
    }

    // Copy the SDL_Surface using SDL_ConvertSurface
    if (source.imageSurface) {
      imageSurface = SDL_ConvertSurface(
        source.imageSurface,
        source.imageSurface->format
      );
    } else {
      imageSurface = nullptr;
    }

    // Copy the other member variables too
    destinationRectangle = source.destinationRectangle;

    return *this;
  }

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

  void ScaleToFit(bool scale) {
    scaleToFit = scale;
  }

  void SaveToFile(const std::string& location) const {
    if (!imageSurface) return;
    IMG_SavePNG(imageSurface, location.c_str());
  }

private:
  SDL_Surface* imageSurface{nullptr};
  SDL_Rect sourceRectangle{};
  // with SDL_BlitSurfaceScaled, width & height of destination rectangle are no longer ignored
  SDL_Rect destinationRectangle{0, 0, 0, 0};
  bool scaleToFit = false;
};