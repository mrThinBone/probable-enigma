#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Text.h"

class TruncatedText : public Text {
 public:
  TruncatedText(
    std::string content,
    const char* fontFile,
    float fontSize,
    int maxWidth
  ) : Text{content, fontFile, fontSize} {
    size_t maxCharacters;
    TTF_MeasureString(
      font, content.c_str(), 0,
      maxWidth, nullptr, &maxCharacters
    );

    if (maxCharacters < content.size()) {
      content.resize(maxCharacters - 3);
      content.append("...");
    }

    CreateSurface(content);
  }
};