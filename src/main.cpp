#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <chrono>

#include "Globals.h"
#include "Engine/Window.h"
#include "Next/World.h"
#include "Next/Goblin.h"
#include "Next/Spawner.h"

// download assets at https://www.studyplan.dev/sdl3/sdl3-minesweeper-engine-overview
using namespace std::chrono;

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


  auto start{high_resolution_clock::now()};
  
  Spawner enemySpawner;
  
  auto end{high_resolution_clock::now()};
  duration<double> timeDelta{end - start};
  std::cout << "TimeDelta: "
    << timeDelta.count()
    << " Seconds ("
    << duration_cast<nanoseconds>(end - start).count()
    << ')';

  SDL_Event event;
  bool shouldQuit{false};
  Uint64 previousFrame{0};

  while (!shouldQuit) {
    Uint64 startTimer{SDL_GetPerformanceCounter()};

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        shouldQuit = true;
      } else if (event.type == SDL_EVENT_KEY_DOWN) {
        enemySpawner.HandleKeyDownEvent(event.key);
      }
    }

    // Update Objects
    Uint64 thisFrame{SDL_GetTicks()};
    Uint64 timeDelta2{thisFrame - previousFrame};
    
    previousFrame = thisFrame;


    // Render Objects
    gameWindow.Render();

    gameWindow.Update();

    // SDL_Delay(1000);
    Uint64 endTimer{SDL_GetPerformanceCounter()};
    Uint64 elapsed{endTimer - startTimer};
    std::cout << "\nElapsed Time: " << elapsed << " ticks";
    std::cout << SDL_GetPerformanceFrequency();
    /*
    A return value of 1,000 would mean it uses milliseconds
  A return value of 1,000,000 would mean it uses microseconds
  A return value of 1,000,000,000 would mean it uses nanoseconds
    */
  }

  TTF_Quit();
  SDL_Quit();
  return 0;
}