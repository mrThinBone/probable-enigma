#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "ImageComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "AssetManager.h" 

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

  TransformComponent* transform{ GetOwner()->GetTransformComponent() };

  if (transform) {
    std::cout << "ImageComponent (" << imageFilePath << 
              ") ready to render at: " << transform->GetPosition() << '\n';
  } else {
    std::cout << "ImageComponent ("
      << imageFilePath
      << ") ready, but no TransformComponent found\n";
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