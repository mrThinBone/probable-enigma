#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Globals.h"
#include "Engine/Window.h"
#include "Snake/SnakeUI.h"

int main(int, char**) {
  SDL_Init(SDL_INIT_VIDEO);
  Utils::CheckSDLError("Initializing SDL");

  TTF_Init();
  Utils::CheckSDLError("Initializing SDL_ttf");

  Engine::Window gameWindow{};
  SnakeUI UI{};

  Uint64 previousTick{SDL_GetTicks()};
  Uint64 currentTick;
  Uint64 deltaTime;

  SDL_Event event;
  bool IsRunning = true;
  while (IsRunning) {
    currentTick = SDL_GetTicks();
    deltaTime = currentTick - previousTick;

    // events
    while (SDL_PollEvent(&event)) {
      UI.HandleEvent(event);
      if (event.type == SDL_EVENT_QUIT) {
        IsRunning = false;
      }
    }

    // Tick
    UI.Tick(deltaTime);

    // Render
    gameWindow.Render();
    UI.Render(gameWindow.GetSurface());

    // Swap
    gameWindow.Update();

    previousTick = currentTick;
  }

  TTF_Quit();
  SDL_Quit();
  return 0;
}