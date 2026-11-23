#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <optional> 
#include "Component.h"

// https://www.studyplan.dev/sdl3/sdl3-entity-scaling#scaling-modes
enum class ScalingMode {
  None, Fill, Contain, Cover
};

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
  void DrawDebugHelpers(SDL_Surface*) override;

  bool LoadNewImage(const std::string& newPath);

  int GetSurfaceWidth() const;
  int GetSurfaceHeight() const;

  void SetWidth(float newWidth);
  void SetHeight(float newHeight);
  void ResetWidth();
  void ResetHeight();
  float GetWidth() const;
  float GetHeight() const;

  void SetScalingMode(ScalingMode mode); 

  void SetOffset(const Vec2& newOffset) { 
    offset = newOffset; 
  }

private:
  // SDL_Surface* imageSurface{nullptr};

  // shared ptr with AssetManager
  std::shared_ptr<SDL_Surface> imageSurface{ nullptr };
  std::string imageFilePath;
  Vec2 offset{ 0, 0 }; // Default to no offset 

  std::optional<float> width{ std::nullopt };
  std::optional<float> height{ std::nullopt };
  ScalingMode scaleMode{ ScalingMode::Fill }; // Default to Fill mode

  // We don't need this any more, either
  // void LoadSurfaceInternal();
};