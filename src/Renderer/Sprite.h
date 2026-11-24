#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include <cassert>

class Sprite {
public:
    Sprite() {};
    Sprite(SDL_Renderer* renderer, const std::string& imagePath, const SDL_FRect& dstRect) {
        SDL_Surface* surface = SDL_LoadBMP(imagePath.c_str());
        // vecteezy walk sprites
        // 1920x1280
        // each = 640x640
        if (surface == nullptr) {
            std::cerr << "Failed to load BMP: " << SDL_GetError() << std::endl;
            assert(0 && "Not able to load BMP");
        }
        m_srcRect = SDL_FRect {0, 0, 640, 640}; // srcrect
        m_totalXFrame = 3;
        m_totalYFrame = 2;

        m_centerPoint = SDL_FPoint {
            .x = m_srcRect.w / 2,
            .y = m_srcRect.h / 2
        };

        const SDL_PixelFormatDetails *pfd = SDL_GetPixelFormatDetails(surface->format);
        Uint32 colorKey = SDL_MapRGB(pfd, nullptr, 0xFF, 0xFF, 0xFF); // white color key
        // blank out those white pixels to transparent
        SDL_SetSurfaceColorKey(surface, true, colorKey);

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

        /*SDL_RenderTexture(
            renderer,
            mTexture,
            &m_srcRect, // portion of texture to draw
            &m_dstRect // portion of window to draw
        );*/
        SDL_RenderTextureRotated(
            renderer,
            mTexture,
            &m_srcRect, // portion of texture to draw
            &m_dstRect, // portion of window to draw
            0.0, // angle
            &m_centerPoint, // center point: imporant for angle
            faceFront ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL // flip
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

    void Tick(Uint64 deltaTime) {
        elapsedTime += deltaTime;
        if (elapsedTime > 400) {
            NextSprite();
            elapsedTime = 0;
        }
    }

    void NextSprite() {
        if (m_xFrameIndex < m_totalXFrame - 1) {
            ++m_xFrameIndex;
        } else if (m_yFrameIndex < m_totalYFrame - 1) {
            ++m_yFrameIndex;
            m_xFrameIndex = 0;
        } else {
            m_xFrameIndex = 0;
            m_yFrameIndex = 0;
        }
        m_srcRect.x = static_cast<float>(m_xFrameIndex * m_srcRect.w);
        m_srcRect.y = static_cast<float>(m_yFrameIndex * m_srcRect.h);
    }

    void Turn() {
        faceFront = !faceFront;
    }

private:
    SDL_Texture* mTexture;
    SDL_FRect m_dstRect;
    
    SDL_FRect m_srcRect;
    int m_xFrameIndex = 0;
    int m_yFrameIndex = 0;
    int m_totalXFrame;
    int m_totalYFrame;
    Uint64 elapsedTime = 0;

    SDL_FPoint m_centerPoint;
    bool faceFront = true;
};