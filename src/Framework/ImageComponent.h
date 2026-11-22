#pragma once
#include <string>
#include <SDL3/SDL.h>
#include "Component.h"

class ImageComponent : public Component {
 public:
  using Component::Component;
  ImageComponent(
    Entity* owner,
    const std::string& filePath
  );
/*
  No custom destructor, copy/move ops needed!

  // Copy Semantics
  ImageComponent(const ImageComponent& other);
  ImageComponent& operator=(const ImageComponent& other);

  // Move Semantics
  ImageComponent(ImageComponent&& other) noexcept;
  ImageComponent& operator=(ImageComponent&& other) noexcept;

  ~ImageComponent() override;
*/
  void Initialize() override;
  void Render(SDL_Surface* surface) override;

  bool LoadNewImage(const std::string& newPath);

private:
  // SDL_Surface* imageSurface{nullptr};

  std::shared_ptr<SDL_Surface> imageSurface{nullptr};
  std::string imageFilePath;

  // We don't need this any more, either
  // void LoadSurfaceInternal();
};