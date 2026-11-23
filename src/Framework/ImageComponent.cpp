#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "ImageComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "AssetManager.h"
#include "Utilities.h"

/*
The core idea for implementing our scaling modes will be calculating the correct srcrect and dstrect based on the ScaleMode, 
the image dimensions, and the target Width/Height.

https://www.studyplan.dev/sdl3/sdl3-entity-scaling#scaling-modes
*/
namespace {
  struct BlitInfo {
    SDL_Rect sourceRect;
    SDL_Rect destRect;
  };

  // Helper function to calculate source and
  // destination rectangles
  BlitInfo CalculateBlitInfo(
    ScalingMode mode,
    // Natural surface dimensions
    int surfaceW, int surfaceH,
    // Target top-left screen position
    float targetX,  float targetY,
    // Target rendering dimensions
    float targetW, float targetH
  ) {
    BlitInfo info;

    // Default to rendering the whole image
    info.sourceRect = {0, 0, surfaceW, surfaceH};

    if (mode == ScalingMode::Cover) {
      float scale{ std::max(targetW/surfaceW, targetH/surfaceH) };

      if (scale * surfaceW > targetW) {
        float clipW { targetW / scale };
        info.sourceRect = Utilities::Round({
          0, 0,
          clipW,
          static_cast<float>(surfaceH)
        });

      } else if (scale * surfaceH > targetH) {
        float clipH { targetH / scale };
        info.sourceRect = Utilities::Round({
          0, 0,
          static_cast<float>(surfaceW),
          clipH
        });
      }
      
      info.destRect = Utilities::Round({ targetX, targetY, targetW, targetH });

      return info;
    }

    if (mode == ScalingMode::Fill) {
      // Stretch source to fill the exact target dimensions
      info.destRect = Utilities::Round({
        targetX, targetY, targetW, targetH
      });
      return info;
    }

    if (mode == ScalingMode::Contain) {
      float scale{ std::min(targetW/surfaceW, targetH/surfaceH) };

      info.destRect = Utilities::Round({
        targetX, targetY,
        surfaceW * scale,
        surfaceH * scale
      });

      return info;
    }

    // default: mode == ScalingMode::None
    // Render at natural image size and at the target position
    info.destRect = Utilities::Round({
      targetX,
      targetY,
      static_cast<float>(surfaceW),
      static_cast<float>(surfaceH)
    });

    return info;
  }
}

ImageComponent::ImageComponent(
  Entity* owner,
  const std::string& filePath
) : Component(owner),
    imageFilePath(filePath) {

  // imageSurface = IMG_Load(filePath.c_str());
  imageSurface = GetAssetManager().LoadSurface(imageFilePath);

  if (!imageSurface) {
    std::cerr
      << "Failed to load image: " << filePath
      << " Error: " << SDL_GetError() << '\n';
  } else {
    std::cout << "Loaded image: " << filePath << '\n';
  }
}

void ImageComponent::Render(SDL_Surface* surface) {
  if (!imageSurface) return;

  //TransformComponent* transform{ GetOwner()->GetTransformComponent() };
  auto [targetX, targetY] { GetOwnerPosition() + offset };
  float targetW { GetWidth() * GetOwnerScale() };
  float targetH { GetHeight() * GetOwnerScale() };

  int surfaceW { GetSurfaceWidth() };
  int surfaceH { GetSurfaceHeight() };

  BlitInfo info { 
    CalculateBlitInfo(
      scaleMode,
      surfaceW, surfaceH,
      targetX, targetY,
      targetW, targetH
    ) 
  };

  if (!SDL_BlitSurfaceScaled(
    imageSurface.get(),
    &info.sourceRect,
    surface,
    &info.destRect,
    SDL_SCALEMODE_LINEAR
  )) {
    std::cerr << "Error: Blit failed: " << SDL_GetError() << '\n';
  }
}

void ImageComponent::Initialize() {
  Entity* owner{GetOwner()};

  if (!owner->GetTransformComponent()) {
    std::cout <<
      "Error: ImageComponent requires"
      " TransformComponent on its Owner\n";

    owner->RemoveComponent(this);
  }
}

bool ImageComponent::LoadNewImage(const std::string& newPath) {
  // Store the new file path
  imageFilePath = newPath;

  // Use our asset manager
  imageSurface = GetAssetManager().LoadSurface(newPath);

  // Return true if the load was
  // successful (surface is not null)
  return imageSurface != nullptr;
}

void ImageComponent::DrawDebugHelpers(SDL_Surface* surface) {
  if (!imageSurface) return;

  // Gather our position and dimensions for
  // the CalculateBlitInfo() function,
  // similar to what we did in Render()
  auto [targetX, targetY]{
    GetOwnerPosition() + offset
  };
  float ownerScale{ GetOwnerScale() };
  float targetW{ GetWidth() * ownerScale };
  float targetH{ GetHeight() * ownerScale };
  int surfaceW{ GetSurfaceWidth() };
  int surfaceH{ GetSurfaceHeight() };

  // 1. Draw Natural Bounds (Green Outline)
  SDL_Rect naturalBounds{
    Utilities::Round({
      targetX, targetY,
      surfaceW * ownerScale,
      surfaceH * ownerScale
    })};

  Utilities::DrawRectOutline(
    surface, naturalBounds,
    SDL_MapRGB(
      SDL_GetPixelFormatDetails(surface->format),
      nullptr, 0, 255, 0
    )
  );

  // 2. Draw Rendered Bounds (Red Outline)
  BlitInfo info{CalculateBlitInfo(
    scaleMode,
    surfaceW, surfaceH,
    targetX, targetY,
    targetW, targetH
  )};

  Utilities::DrawRectOutline(
    surface, info.destRect,
    SDL_MapRGB(
      SDL_GetPixelFormatDetails(surface->format),
      nullptr, 255, 0, 0
    )
  );

  // Continue to draw the position
  // marker from before (Blue Square)
  SDL_Rect debugRect{Utilities::Round({
      targetX - 5, targetY - 5, 10, 10 })};

  SDL_FillSurfaceRect(surface, &debugRect, SDL_MapRGB(
    SDL_GetPixelFormatDetails(surface->format),
    nullptr, 0, 0, 255));
}

int ImageComponent::GetSurfaceWidth() const {
  if (!imageSurface) {
    std::cerr << "Warning: Attempted to get "
      "width from null ImageSurface.\n";
    return 0;
  }
  return imageSurface->w;
}

int ImageComponent::GetSurfaceHeight() const {
  if (!imageSurface) {
    std::cerr << "Warning: Attempted to get "
      "height from null ImageSurface.\n";
    return 0;
  }
  return imageSurface->h;
}

void ImageComponent::SetWidth(float newWidth) {
  width = newWidth;
}

void ImageComponent::SetHeight(float newHeight) {
  height = newHeight;
}

void ImageComponent::ResetWidth() {
  width = std::nullopt;
}

void ImageComponent::ResetHeight() {
  height = std::nullopt;
}

float ImageComponent::GetWidth() const {
  // If Width has a value, return it.
  // Otherwise, return surface width.
  return width.value_or(GetSurfaceWidth());
}

float ImageComponent::GetHeight() const {
  // If Height has a value, return it.
  // Otherwise, return surface height.
  return height.value_or(GetSurfaceHeight());
}

void ImageComponent::SetScalingMode(ScalingMode mode) {
  scaleMode = mode;
}

/*
ImageComponent::~ImageComponent() {
  SDL_DestroySurface(imageSurface);
  imageSurface = nullptr;
}

// Copy Constructor
ImageComponent::ImageComponent(const ImageComponent& other)
  : Component(other.GetOwner()),
    imageFilePath(other.imageFilePath) {

  LoadSurfaceInternal();

}

// Copy Assignment
ImageComponent& ImageComponent::operator=(const ImageComponent& other) {
  // 1. Check for self-assignment
  if (this == &other) {return *this;}

  // 2. Copy base class members (the Owner
  // entity, in this case)
  Component::operator=(other);

  // 3. Copy this class's members
  imageFilePath = other.imageFilePath;

  // 4. Handle the resource (deep copy)
  // LoadSurfaceInternal() conveniently freeing
  // the old surface and loading the new one.
  LoadSurfaceInternal();

  // 5. Return reference to self
  return *this;
}

// Move Constructor
ImageComponent::ImageComponent(ImageComponent&& other) noexcept
  : Component(other.GetOwner()),
    // Steal the resource pointer
    imageSurface(other.imageSurface),
    // Move the file path string efficiently
    imageFilePath(std::move(other.imageFilePath)) 
{
  // Important: Null out Other's pointer so its
  // destructor doesn't free the surface we just took!
  other.imageSurface = nullptr;
}

// Move Assignment
ImageComponent& ImageComponent::operator=(ImageComponent&& other) noexcept {
  // 1. Check for self-assignment
  if (this == &other) { return *this; }

  // 2. Release *our* current resource *before*
  // taking Other's
  SDL_DestroySurface(imageSurface);

  // 3. Steal Other's resource pointer
  imageSurface = other.imageSurface;

  // 4. Move other members
  Component::operator=(std::move(other));
  imageFilePath = std::move(other.imageFilePath);

  // 5. Null out Other's pointer
  other.imageSurface = nullptr;

  // 6. Return reference to self
  return *this;
}

void ImageComponent::LoadSurfaceInternal() {
  // 1. Free existing surface if there is one
  if (imageSurface) {
    SDL_DestroySurface(imageSurface);
    imageSurface = nullptr;
  }

  // 2. Load new surface if path is not empty
  if (!imageFilePath.empty()) {
    imageSurface = IMG_Load(imageFilePath.c_str());
    if (!imageSurface) {
      std::cerr
        << "Failed to load image: "
        << imageFilePath
        << " Error: " << SDL_GetError() << '\n';
    } else {
      std::cout << "Loaded image: "
        << imageFilePath << '\n';
    }
  }
}
*/