#pragma once
#include <SDL3/SDL.h>
#include <iostream>

struct SpawnerConfig {
  float intervalMultiplier;
  Uint32 minInterval;
};

Uint32 SpawnGoblin(
  void* userdata,
  SDL_TimerID timerID,
  Uint32 interval
) {
  std::cout << "Spawning a Goblin - Delay: " << interval << " \n";

  SpawnerConfig* config{ static_cast<SpawnerConfig*>(userdata) };

  Uint32 nextDelay{static_cast<Uint32>(
    interval * config->intervalMultiplier
  )};

  return std::max(nextDelay, config->minInterval);
}

class Spawner {
public:
  void HandleKeyDownEvent(
    SDL_KeyboardEvent& E
  ) {
    if (E.key == SDLK_SPACE) {
      StartTimer();
    }
  }

  void StartTimer() {
    if (mTimer != 0) {
      std::cout << "Already spawning - ignoring event\n";
    } else {
      std::cout << "Starting Spawner\n";
      SDL_TimerID timer{ SDL_AddTimer(1000, SpawnGoblin, &config) };

      if (!timer) {
        std::cout << "Error creating timer: " << SDL_GetError();
      } else {
        mTimer = timer;
        std::cout << "Timer created with ID: " << timer << "\n";
      }
    }
  }

  void RemoveTimer() {
    std::cout << "Removing Timer: ";
    if(SDL_RemoveTimer(mTimer)) {
      std::cout << "Timer with ID " << mTimer
       << " Removed Successfully\n";
      mTimer = 0;
    } else {
      std::cout << "Timer with ID " << mTimer
        << " was not found\n";
    }
  }


private:
  SpawnerConfig config{0.8f, 600};
  SDL_TimerID mTimer{0};
};