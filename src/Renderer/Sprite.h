#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include <cassert>

class Sprite {
public:
    Sprite() {};
    Sprite(SDL_Renderer* renderer, const std::string& imagePath, const SDL_FRect& dstRect) {
        SDL_Surface* surface = SDL_LoadBMP(imagePath.c_str());
        if (surface == nullptr) {
            std::cerr << "Failed to load BMP: " << SDL_GetError() << std::endl;
            assert(0 && "Not able to load BMP");
        }
        mTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);

        m_dstRect = dstRect;
    }

    Sprite(const Sprite&) = delete; // Copy constructor
    Sprite& operator=(const Sprite&) = delete; // Copy assignment operator
    // Move constructor
    Sprite(Sprite&& other) noexcept {
        // std::swap(mTexture, other.mTexture);
        this->mTexture = other.mTexture;
        other.mTexture = nullptr;
    }
    // Move assignment operator
    Sprite& operator=(Sprite&& other) noexcept {
        this->mTexture = other.mTexture;
        other.mTexture = nullptr;
        return *this;
    }
    
    ~Sprite() {
        if (mTexture != nullptr) {
            SDL_DestroyTexture(mTexture);
        }
    }

    void Render(SDL_Renderer* renderer) {
        if (mTexture == nullptr) return;

        SDL_RenderTexture(
            renderer,
            mTexture,
            nullptr, // portion of texture to draw
            &m_dstRect // portion of window to draw
        );
    }

    void SetPosition(int x, int y) {
        m_dstRect.x = x;
        m_dstRect.y = y;
    }

    void SetDimension(int w, int h) {
        m_dstRect.w = w;
        m_dstRect.h = h;
    }

private:
    SDL_Texture* mTexture;
    SDL_FRect m_dstRect;
    int m_x;
    int m_y;
};