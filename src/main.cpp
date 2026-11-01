#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Window.h"
#include "UI.h"

void HandleEvent(SDL_Event& e) {
  if (e.type == SDL_EVENT_MOUSE_MOTION) {
    std::cout << "Mouse moved\n";
  } else if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    std::cout << "Mouse clicked\n";
  } else if (e.type == SDL_EVENT_KEY_DOWN) {
    std::cout << "Keyboard button pressed\n";
  }
}

int main(int, char **)
{
  // Initialization
  SDL_Init(SDL_INIT_VIDEO);
  Window gameWindow;
  //const SDL_PixelFormatDetails *Fmt = SDL_GetPixelFormatDetails(GameWindow.GetSurface()->format);

  UI uiManager;

  // rect.SetHoverColor(SDL_MapRGBA(Fmt, nullptr, 0, 0, 255, 255));

  bool isRunning = true;
  SDL_Event event;
  while (isRunning)
  {
    // 1. Process Events
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
      {
        isRunning = false;
        SDL_Quit();
        return 0;
      } else {
        HandleEvent(event);
        uiManager.HandleEvent(event);
      }
    }
    // 2. Update Objects
    

    // 3. Render Changes
    gameWindow.Render();
    uiManager.Render(gameWindow.GetSurface());

    gameWindow.Update(); // swap buffers
  }

  SDL_Quit();
  return 0;
}