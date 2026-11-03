#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Window.h"
#include "UI.h"
#include "Image.h"
#include "Text.h"
#include "ErrorHandling.h"

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
  TTF_Init();
  if (!TTF_Init()) {
    std::cout << "Error initializing SDL_ttf: " << SDL_GetError() << std::endl;
  }
  Window gameWindow(700, 350);
  //const SDL_PixelFormatDetails *Fmt = SDL_GetPixelFormatDetails(GameWindow.GetSurface()->format);

  // std::string BASE_PATH{SDL_GetBasePath()};
  // std::string IMAGE_PATH{BASE_PATH + "Assets/box.png"};
  //UI uiManager;
  //CheckSDLError("SDL_Init");
  // find fonts cmd-line : fc-list | grep Roboto
  Text helloText{"Hello World", "/usr/share/fonts/truetype/noto/NotoSansDisplay-Regular.ttf"};
  helloText.Position(50, 50);
  // helloText.SetScale(4,4);

  // Image example(IMAGE_PATH); // see different in perf
  // Image example(IMAGE_PATH);
  // example.ScaleToFit(true);
  //CheckSDLError("LoadImage");

  // example.Crop(0, 0, 100, 50);
  
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
        //uiManager.HandleEvent(event);
      }
    }
    // 2. Update Objects
    

    // 3. Render Changes
    gameWindow.Render();
    // uiManager.Render(gameWindow.GetSurface());
    Uint64 start{SDL_GetPerformanceCounter()};
    // example.Render(gameWindow.GetSurface());
    Uint64 delta{SDL_GetPerformanceCounter() - start};
    std::cout << "Time to Render Image: " << delta << '\n';
    helloText.Render(gameWindow.GetSurface());

    gameWindow.Update(); // swap buffers
  }

  TTF_Quit();
  SDL_Quit();
  return 0;
}