#include "ImageComponent.h"
#include "Entity.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "TransformComponent.h"

ImageComponent::ImageComponent(
  Entity* owner,
  const std::string& filePath
) : Component(owner),
    imageFilePath(filePath) {

  imageSurface = IMG_Load(filePath.c_str());

  if (!imageSurface) {
    std::cerr
      << "Failed to load image: " << filePath
      << " Error: " << SDL_GetError() << '\n';
  } else {
    std::cout << "Loaded image: "
      << filePath << '\n';
  }
}

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
  if (this == &other) {return *this;}

  Component::operator=(other);
  imageFilePath = other.imageFilePath;
  LoadSurfaceInternal();
  return *this;
}

// Move Constructor
ImageComponent::ImageComponent(ImageComponent&& other) noexcept
  : Component(other.GetOwner()),
    imageSurface(other.imageSurface),
    imageFilePath(std::move(
      other.imageFilePath)) {
  other.imageSurface = nullptr;
}

// Move Assignment
ImageComponent& ImageComponent::operator=(ImageComponent&& other) noexcept {
  if (this == &other) { return *this; }

  Component::operator=(std::move(other));

  SDL_DestroySurface(imageSurface);
  imageSurface = other.imageSurface;
  imageFilePath = std::move(other.imageFilePath);
  other.imageSurface = nullptr;
  return *this;
}

void ImageComponent::Render(SDL_Surface* Surface) {
  if (!imageSurface) return;

  TransformComponent* transform{
    GetOwner()->GetTransformComponent()};

  if (transform) {
    std::cout << "ImageComponent ("
      << imageFilePath
      << ") ready to render at: "
      << transform->GetPosition() << '\n';
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

void ImageComponent::LoadSurfaceInternal() {
  if (imageSurface) {
    SDL_DestroySurface(imageSurface);
    imageSurface = nullptr;
  }

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