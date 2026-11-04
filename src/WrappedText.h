#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Text.h"


class WrappedText : public Text {
 public:
  WrappedText(
    const std::string& content,
    const char* fontFile,
    float fontSize, int maxWidth,
    TTF_HorizontalAlignment alignment
      = TTF_HORIZONTAL_ALIGN_CENTER
  ) : Text{content, fontFile, fontSize}, maxWidth{maxWidth} {
    TTF_SetFontWrapAlignment(font, alignment);
    CreateSurface(content);
  }

private:
  void CreateSurface(const std::string& Content) {
    SDL_DestroySurface(textSurface);
    textSurface = TTF_RenderText_Blended_Wrapped(
      font, Content.c_str(), 0,
      {255, 255, 255, 255}, maxWidth
    );
    if (!textSurface) {
      std::cout << "Error creating TextSurface: "
        << SDL_GetError() << '\n';
    }
  }

  int maxWidth;
};