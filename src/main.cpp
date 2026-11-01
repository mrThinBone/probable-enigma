#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Window.h"
#include "UI.h"

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
  //const SDL_PixelFormatDetails *Fmt = SDL_GetPixelFormatDetails(GameWindow.GetSurface()->format);

  UI UIManager;

  // Rect.SetHoverColor(SDL_MapRGBA(Fmt, nullptr, 0, 0, 255, 255));

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
        UIManager.HandleEvent(Event);
      }
    }
    // 2. Update Objects
    

    // 3. Render Changes
    GameWindow.Render();
    UIManager.Render(GameWindow.GetSurface());

    GameWindow.Update(); // swap buffers
  }

  SDL_Quit();
  return 0;
}