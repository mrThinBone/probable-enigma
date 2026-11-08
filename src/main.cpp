#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Globals.h"
#include "Engine/Window.h"
#include "Minesweeper/UI.h"

// download assets at https://www.studyplan.dev/sdl3/sdl3-minesweeper-engine-overview

int main(int, char**){
  SDL_Init(SDL_INIT_VIDEO);
#ifdef SHOW_DEBUG_HELPERS
  Utils::CheckSDLError("SDL_Init");
#endif

  TTF_Init();
#ifdef SHOW_DEBUG_HELPERS
  Utils::CheckSDLError("TTF_Init");
#endif

  Engine::Window gameWindow;
  MinesweeperUI UI;

  SDL_Event event;
  bool shouldQuit{false};

  while (!shouldQuit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        shouldQuit = true;
      } else { UI.HandleEvent(event); }
    }
    gameWindow.Render();
    UI.Render(gameWindow.GetSurface());
    gameWindow.Update();
  }

  TTF_Quit();
  SDL_Quit();
  return 0;
}