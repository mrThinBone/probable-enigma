#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "../Globals.h"

namespace Engine{
  class Text {
  public:
    Text(
      int x, int y, int w, int h,
      const std::string& Content,
      SDL_Color color = {0, 0, 0, 255},
      float FontSize = 30.0f
    ) : destinationRect{x, y, w, h},
        color{color}
    {
      font = TTF_OpenFont(
        Config::FONT.c_str(), FontSize);
#ifdef SHOW_DEBUG_HELPERS
      Utils::CheckSDLError("TTF_OpenFont");
#endif
      SetText(Content);
    }

    void SetText(const std::string& text){
      SetText(text, color);
    }

    void SetText(const std::string& text,
                 SDL_Color newColor){
      if (textSurface) {
        SDL_DestroySurface(textSurface);
      }
      color = newColor;

      textSurface = TTF_RenderText_Blended(
        font, text.c_str(), 0, color
      );

      auto [x, y, w, h] = destinationRect;
      // Horizontally centering
      const int widthDifference{w - textSurface->w};
      const int leftOffset{widthDifference / 2};

      // Vertically centering
      const int heightDifference{h - textSurface->h};
      const int topOffset{heightDifference / 2};

      textPosition = {
        x + leftOffset, y + topOffset,
        textSurface->w, textSurface->h
      };
    }

    void Render(SDL_Surface* Surface) {
      SDL_BlitSurface(
        textSurface, nullptr,
        Surface, &textPosition
      );
    }

    ~Text() {
      if (TTF_WasInit()) {
        TTF_CloseFont(font);
      }
      if (textSurface) {
        SDL_DestroySurface(textSurface);
      }
    }

    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;

  private:
    SDL_Surface* textSurface{nullptr};
    TTF_Font* font{nullptr};
    SDL_Rect destinationRect{0, 0, 0, 0};
    SDL_Rect textPosition{0, 0, 0, 0};
    SDL_Color color{0, 0, 0, 255};
  };
}