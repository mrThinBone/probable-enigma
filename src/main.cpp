#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Window.h"

void HandleEvent(SDL_Event& E) {
  if (E.type == SDL_EVENT_MOUSE_MOTION) {
    std::cout << "Mouse moved\n";
  } else if (E.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    std::cout << "Mouse clicked\n";
  } else if (E.type == SDL_EVENT_KEY_DOWN) {
    std::cout << "Keyboard button pressed\n";
  }
}

int main(int, char **)
{
  // Initialization
  SDL_Init(SDL_INIT_VIDEO);
  Window GameWindow;

  bool IsRunning = true;
  SDL_Event Event;
  while (IsRunning)
  {
    // 1. Process Events
    while (SDL_PollEvent(&Event))
    {
      if (Event.type == SDL_EVENT_QUIT)
      {
        IsRunning = false;
        SDL_Quit();
        return 0;
      } else {
        HandleEvent(Event);
      }
    }
    // 2. Update Objects
    

    // 3. Render Changes
    GameWindow.Render();
  }

  SDL_Quit();
  return 0;
}