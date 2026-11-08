#pragma once

#define SHOW_DEBUG_HELPERS

#include <iostream>
#include <SDL3/SDL.h>
#include <string>

namespace UserEvents{}

namespace Config{
  // Game Settings
  inline const std::string GAME_NAME{
    "Minesweeper"};

  // Size and Positioning
  inline constexpr int WINDOW_HEIGHT{200};
  inline constexpr int WINDOW_WIDTH{400};

  // Colors
  inline constexpr SDL_Color BACKGROUND_COLOR{
    170, 170, 170, 255};
  inline constexpr SDL_Color BUTTON_COLOR{
    200, 200, 200, 255};
  inline constexpr SDL_Color BUTTON_HOVER_COLOR{
    220, 220, 220, 255};

  // Asset Paths
  inline const std::string BASE_PATH{
    SDL_GetBasePath()};
  inline const std::string BOMB_IMAGE{
    BASE_PATH + "Assets/bomb_64.png"};
  inline const std::string FLAG_IMAGE{
    BASE_PATH + "Assets/Flag_64.png"};
  inline const std::string FONT{
    BASE_PATH + "Assets/Roboto-Medium.ttf"};
}

namespace Utils{
#ifdef SHOW_DEBUG_HELPERS
  inline void CheckSDLError(
    const std::string& Msg){
    const char* error = SDL_GetError();
    if (*error != '\0') {
      std::cerr << Msg << " Error: " << error <<
        '\n';
      SDL_ClearError();
    }
  }
#endif
}