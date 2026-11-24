#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Window.h"
#include "Scene.h"

int main(int argc, char* argv[]) {
  SDL_Init(SDL_INIT_VIDEO);

  Window GameWindow;
  Scene GameScene;

  SDL_Event Event;
  bool IsRunning{true};
  Uint64 LastTick{SDL_GetPerformanceCounter()};

  while (IsRunning) {
    while (SDL_PollEvent(&Event)) {
      GameScene.HandleEvent(Event);
      if (Event.type == SDL_EVENT_QUIT) {
        IsRunning = false;
      }
    }

    Uint64 CurrentTick{SDL_GetPerformanceCounter()};
    float DeltaTime{float(CurrentTick - LastTick) /
      float(SDL_GetPerformanceFrequency()
    )};
    LastTick = CurrentTick;

    GameScene.Tick(DeltaTime);

    GameWindow.Render();
    GameScene.Render(GameWindow.GetSurface());
    
    GameWindow.Update();
  }

  SDL_Quit();
  return 0;
}