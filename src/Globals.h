#pragma once

#define SHOW_DEBUG_HELPERS

#include <iostream>
#include <SDL3/SDL.h>
#include <string>

namespace UserEvents{
  inline const Uint32 CELL_CLEARED{
    SDL_RegisterEvents(1)};
}

namespace Config{
  // Game Settings
  inline const std::string GAME_NAME{
    "Snake"};
  inline constexpr int GRID_COLUMNS{8};
  inline constexpr int GRID_ROWS{4};

  // Size and Positioning
  inline constexpr int PADDING{5};
  inline constexpr int CELL_SIZE{50};

  inline constexpr int GRID_HEIGHT{
    CELL_SIZE * GRID_ROWS
    + PADDING * (GRID_ROWS - 1)
  };

  inline constexpr int GRID_WIDTH{
    CELL_SIZE * GRID_COLUMNS +
    PADDING * (GRID_COLUMNS - 1)};

  inline constexpr int WINDOW_HEIGHT{
    //GRID_HEIGHT + PADDING * 2
    400
  };
  inline constexpr int WINDOW_WIDTH{
    //GRID_WIDTH + PADDING * 2
    800
  };

  inline constexpr SDL_Color BUTTON_CLEARED_COLOR{
    240, 240, 240, 255};
  // ...

  // Colors
  inline constexpr SDL_Color BACKGROUND_COLOR{
    85, 138, 52, 255};
  inline constexpr SDL_Color FONT_COLOR{
    255, 255, 255, 255};
  inline constexpr SDL_Color BUTTON_COLOR{
    200, 200, 200, 255};
  inline constexpr SDL_Color BUTTON_HOVER_COLOR{
    220, 220, 220, 255};
  

  // Asset Paths
  inline const std::string BASE_PATH{
    SDL_GetBasePath()};
  inline const std::string BOMB_IMAGE{
    BASE_PATH + "Bomb.png"};
  inline const std::string FLAG_IMAGE{
    BASE_PATH + "Flag.png"};
  inline const std::string FONT{
    BASE_PATH + "Roboto-Medium.ttf"};
}

namespace Utils{
#ifdef SHOW_DEBUG_HELPERS
  inline void CheckSDLError(const std::string& Msg)
  {
    const char* error = SDL_GetError();
    
    if (*error != '\0') {
      std::cerr << Msg << " Error: " << error << '\n';
      SDL_ClearError();
    }
  }
#endif
}