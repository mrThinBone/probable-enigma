#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <SDL3_image/SDL_image.h>
#include <iostream>

// Custom deleter for an SDL_Surface
struct SDLSurfaceDeleter {
  void operator()(SDL_Surface* Surface) const {
    SDL_DestroySurface(Surface);
  }
};

using SurfacePtr = std::shared_ptr<SDL_Surface>;
// Map file path to shared surface pointer
using CacheMap =
  std::unordered_map<std::string, SurfacePtr>;

class AssetManager {
public:
  
  SurfacePtr LoadSurface(const std::string& path) {
    
    if (surfaceCache.find(path) != surfaceCache.end()) {
      // Load a surface, reusing if already loaded
      std::cout << "CACHE HIT: " << path << '\n';
      return surfaceCache[path];
    }

    // Cache Miss - need to load a new surface
    std::cout << "CACHE MISS: " << path << '\n';
    SDL_Surface* surface{IMG_Load(path.c_str())};
    if (!surface) {
      std::cerr << "AssetManager failed to load: "
                << path << " Error: "
                << SDL_GetError() << '\n';
      return nullptr;  // Return null on failure
    }

    SurfacePtr sharedSurface(
      surface, SDLSurfaceDeleter{}
    );

    // Store in cache and return
    surfaceCache[path] = sharedSurface;
    return sharedSurface;
  }

  // Prevent copying/moving
  AssetManager() = default;
  AssetManager(const AssetManager&) = delete;
  AssetManager& operator=(const AssetManager&) = delete;
  AssetManager(AssetManager&&) = delete;
  AssetManager& operator=(AssetManager&&) = delete;

 private:
  CacheMap surfaceCache;
};