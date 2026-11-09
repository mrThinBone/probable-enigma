#pragma once

#define SHOW_DEBUG_HELPERS

#include <iostream>
#include <SDL3/SDL.h>
#include <string>

namespace UserEvents{
  inline const Uint32 CELL_CLEARED{ SDL_RegisterEvents(1) };

  inline const Uint32 ADVANCE{ SDL_RegisterEvents(1) };
  inline const Uint32 APPLE_EATEN{ SDL_RegisterEvents(1) };
  inline const Uint32 RESTART_GAME{ SDL_RegisterEvents(1) };
}

namespace Config{
  // Game Settings
  inline const std::string GAME_NAME{
    "Snake"};
  inline constexpr int GRID_COLUMNS{16};
  inline constexpr int GRID_ROWS{5};

  // Size and Positioning
  inline constexpr int PADDING{5};
  inline constexpr int CELL_SIZE{36};

  inline constexpr int GRID_HEIGHT{
    CELL_SIZE * GRID_ROWS
    + PADDING * (GRID_ROWS - 1)
  };

  inline constexpr int GRID_WIDTH{
    CELL_SIZE * GRID_COLUMNS +
    PADDING * (GRID_COLUMNS - 1)};

  inline constexpr int FOOTER_HEIGHT{60};

  inline constexpr int WINDOW_HEIGHT{
    GRID_HEIGHT 
    + FOOTER_HEIGHT
    + PADDING * 2
  };
  inline constexpr int WINDOW_WIDTH{
    GRID_WIDTH + PADDING * 2
  };

  inline constexpr SDL_Color BUTTON_CLEARED_COLOR{
    240, 240, 240, 255};
  // ...

  // Colors
  inline constexpr SDL_Color BACKGROUND_COLOR{
    85, 138, 52, 255};
  inline constexpr SDL_Color FONT_COLOR{
    255, 255, 255, 255};
  inline constexpr SDL_Color CELL_COLOR_A{
    171, 214, 82, 255};
  inline constexpr SDL_Color CELL_COLOR_B{
    161, 208, 74, 255};
  inline constexpr SDL_Color SNAKE_COLOR{
    67, 117, 234, 255};

  inline constexpr SDL_Color BUTTON_COLOR{
    73, 117, 46, 255};
  inline constexpr SDL_Color BUTTON_HOVER_COLOR{
    220, 220, 220, 255};
  

  // Asset Paths
  inline const std::string BASE_PATH{
    SDL_GetBasePath()};
  inline const std::string BOMB_IMAGE{
    BASE_PATH + "Bomb.png"};
  inline const std::string FLAG_IMAGE{
    BASE_PATH + "Assets/flag_64.png"};
  inline const std::string FONT{
    BASE_PATH + "Assets/Roboto-Medium.ttf"};

  inline constexpr int ADVANCE_INTERVAL{1000};
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