#pragma once
#include <SDL3/SDL.h>
#include <string>
#include "Engine/Text.h"
#include "Assets.h"
#include "Globals.h"

class ScoreCounter {
public:
  ScoreCounter(Assets& assetList)
  : assetList{assetList} {}

  void HandleEvent(const SDL_Event& event) {
    if (event.type == UserEvents::APPLE_EATEN) {
      ++currentScore;
      text.SetText(GetScoreString());
    } else if (event.type == UserEvents::RESTART_GAME) {
      currentScore = 0;
      text.SetText(GetScoreString());
    }
  }

  void Render(SDL_Surface* surface) {
    using namespace Config;
    SDL_FillSurfaceRect(surface, &backgroundRect,
      SDL_MapRGB(
        SDL_GetPixelFormatDetails(surface->format),
        nullptr,
        SCORE_BACKGROUND_COLOR.r,
        SCORE_BACKGROUND_COLOR.g,
        SCORE_BACKGROUND_COLOR.b
      )
    );

    assetList.Apple.Render(surface, &appleRect);
    text.Render(surface, &textRect);
  }

private:
  std::string GetScoreString() {
    return std::to_string(currentScore) + "/"
      + std::to_string(maxScore);
  }

  Assets& assetList;
  int currentScore{0};
  int maxScore{Config::MAX_LENGTH - 2};
  Engine::Text text{GetScoreString(), 40};

  SDL_Rect backgroundRect{
    Config::PADDING,
    Config::GRID_HEIGHT + Config::PADDING * 2,
    maxScore > 99 ? 250 : 190,
    Config::FOOTER_HEIGHT - Config::PADDING};

  SDL_Rect appleRect{
    backgroundRect.x + Config::PADDING,
    backgroundRect.y + Config::PADDING,
    backgroundRect.h - Config::PADDING * 2,
    backgroundRect.h - Config::PADDING * 2};

  SDL_Rect textRect{
    appleRect.x + appleRect.w + Config::PADDING,
    appleRect.y,
    0, 0};
};