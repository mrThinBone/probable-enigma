#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <iostream>

class Text {
 public:
  Text(const std::string& content, const char* fontFile, float fontSize = 25.0f) : font{ TTF_OpenFont(fontFile, fontSize) } {
    if (!font) {
      std::cout << "Error loading font: " << SDL_GetError() << std::endl;
    }
    CreateSurface(content);
  }

  void Render(SDL_Surface* destinationSurface) {

    if (!textSurface) return;

    //SDL_BlitSurface( textSurface, nullptr, destinationSurface, &destinationRectangle);
    SDL_BlitSurfaceScaled(
      textSurface, nullptr, 
      destinationSurface, &destinationRectangle,
      SDL_SCALEMODE_LINEAR
    );
  }

  void SetFontSize(float size) {
    TTF_SetFontSize(font, size);
  }

  void SetScale(float scaleX, float scaleY) {
    destinationRectangle.w = static_cast<int>(textSurface->w * scaleX);
    destinationRectangle.h = static_cast<int>(textSurface->h * scaleY);
  }

  void Position(int x, int y) {
    destinationRectangle.x = x;
    destinationRectangle.y = y;
  }

  void AntiAliasing(bool value) {
    antiAliasing = value;
  }

  void SetBackgroundColor(const SDL_Color& color) {
    bgColor = color;
    shaded = true;
  }

  ~Text() {
    SDL_DestroySurface(textSurface);

    if (TTF_WasInit()) {
      TTF_CloseFont(font);
    }
  }

  Text(const Text&) = delete;
  Text& operator=(const Text&) = delete;

protected:
  TTF_Font* font{nullptr};
  SDL_Surface* textSurface{nullptr};
  SDL_Rect destinationRectangle{0,0,0,0};

  SDL_Color textColor {255, 255, 255, 255}; // White

  bool antiAliasing {true};
  SDL_Color bgColor {0,0,0,0};

  bool shaded{false};

  void CreateSurface(const std::string &content)
  {
    SDL_Surface *newSurface{nullptr};
    // Rasterization: generate pixel data from the provided font and text
    // Blitting:      copy pixel data from one surface to another
    if (antiAliasing) {
      if (shaded) {
        newSurface = TTF_RenderText_Shaded( // Faster Blitting - Shaded
              font,
              content.c_str(),
              0,              // Use the null-terminator to find length
              textColor,      // text color
              bgColor         // Background color
          );
      } else
        newSurface = TTF_RenderText_Blended(
            font,
            content.c_str(),
            0,                            
            textColor 
        );
      
    } else {
      if (shaded) {
        newSurface = TTF_RenderText_LCD( // faster Rasterization and Blitting
              font,
              content.c_str(),
              0,
              textColor,
              bgColor
        );
      } else {
        newSurface = TTF_RenderText_Solid( // Faster Rasterization - Solid
              font,
              content.c_str(),
              0,
              textColor
        );
      }
    }

    if (newSurface)
    {
      SDL_DestroySurface(textSurface);
      textSurface = newSurface;
      
      destinationRectangle.w = textSurface->w;
      destinationRectangle.h = textSurface->h;
    }
    else
    {
      std::cout << "Error creating TextSurface: "
                << SDL_GetError() << '\n';
    }
  }
};