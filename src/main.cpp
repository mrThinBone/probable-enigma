#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Engine/Window.h"
#include "Scene.h"

int main(int argc, char** argv) {
  SDL_Init(SDL_INIT_VIDEO);
  Engine::Window gameWindow;
  Scene gameScene;

  Uint64 lastTick{SDL_GetPerformanceCounter()};
  SDL_Event event;
  bool isRunning = true;

  while (isRunning) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        isRunning = false;
      }
      gameScene.HandleEvent(event);
    }

    Uint64 currentTick{SDL_GetPerformanceCounter()};
    float deltaTime{static_cast<float>(
      currentTick - lastTick) /
      static_cast<float>(SDL_GetPerformanceFrequency())
    };
    lastTick = currentTick;

    // Tick
    gameScene.Tick(deltaTime);

    // Render
    gameWindow.Render();
    gameScene.Render(gameWindow.GetSurface());

    // Swap
    gameWindow.Update();
  }

  SDL_Quit();
  return 0;
}