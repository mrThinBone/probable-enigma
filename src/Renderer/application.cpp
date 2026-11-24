#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include <cassert>
#include "Sprite.h"

// const char* RESOURCES_DIR = "Assets";

// https://wiki.libsdl.org/SDL3/CategoryRender
struct SDLApplication {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Sprite* mSprite;

    bool mRunning = false;

    // Constructor
    SDLApplication(const char* title) {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow(title, 640, 480, 0);

        SDL_Log("Available renderer drivers:");
        for (int i = 0; i < SDL_GetNumRenderDrivers(); i++) {
            SDL_Log("%d. %s", i + 1, SDL_GetRenderDriver(i));
        }
        // nullptr -> let SDL choose the best driver
        renderer = SDL_CreateRenderer(window, nullptr);
        if (renderer == nullptr) {
            std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
            assert(0 && "Not able to create HW accelerated renderer");
        } else {
            const char* driverName = SDL_GetRendererName(renderer);
            std::cout << "Selected driver: " << driverName << std::endl;

            // modes: https://wiki.libsdl.org/SDL3/SDL_RendererLogicalPresentation
            // https://youtu.be/5CiO035hQNA?si=6C2xTiBNH5f40zHa&t=276
            SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_STRETCH);

            SetupSceneData();
        }
    }

    void SetupSceneData() {
        const char* basePath = SDL_GetBasePath();
        std::string assetFolder = std::string(basePath) + "Assets/";
        SDL_FRect spriteRect = { 0, 0, 640, 480 };
        // SDL_FRect spriteRect = { 0, 0, 400, 280 };
        mSprite = new Sprite(renderer, std::string(assetFolder) + "sample.bmp", spriteRect);
    }

    // Destructor
    ~SDLApplication() {
        if (mSprite != nullptr) delete mSprite;
        if (renderer != nullptr) SDL_DestroyRenderer(renderer);
        if (window != nullptr) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Tick() {
        Input();
        Update();
        Render();
    }

    void Input() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                mRunning = false;
            }
            else if (event.type == SDL_EVENT_KEY_DOWN) {
                switch (event.key.key) {
                    case SDLK_ESCAPE:
                        mRunning = false;
                        break;
                    default:
                        break;
                }
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        // Handle left mouse button down
                        break;
                    case SDL_BUTTON_RIGHT:
                        break;
                    case  SDL_BUTTON_MIDDLE:
                        break;
                    default:
                        break;   
                }
                SDL_Log("Clicks: %d", event.button.clicks);
            }
        }

        float x,y;
        // Get the 'local' within current window mouse position
        SDL_MouseButtonFlags mouse = SDL_GetMouseState(&x, &y);

        // SDL_Log("Mouse Position: (%.2f, %.2f)", x, y);
        // SDL_Log("Mouse Button State: %d", mouse);
    }

    void Update() {}

    void Render() {
        SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
        /*const SDL_PixelFormatDetails *Fmt = SDL_GetPixelFormatDetails(windowSurface->format);
        if (windowSurface != nullptr) {
            SDL_FillSurfaceRect(windowSurface, NULL, SDL_MapRGB(Fmt, nullptr, 0, 0, 0));
            SDL_UpdateWindowSurface(window);
        }*/

        // Clear the screen with a solid color
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);
        
        // draw operation in between
        mSprite->Render(renderer);

        // update
        SDL_RenderPresent(renderer);
        
    }

    void MainLoop() {
        mRunning = true;
        
        Uint64 fps = 0;
        Uint64 lastTime = 0;
        while (mRunning) {
            Uint64 currentTime = SDL_GetTicks();
            // each frame
            Tick();
            SDL_Delay(16); // ~16ms, fps = 1000ms(1s) / 16ms(1 frame)
            fps++;
            // Per frame calculation of elapsed time
            Uint64 deltaTime = SDL_GetTicks() - currentTime;

            // FPS calculation
            if (currentTime > lastTime + 1000) {
                std::cout << "FPS: " << fps << std::endl;
                fps = 0;
                lastTime = currentTime;
            }
        }
    }
};

int main(int argc, char* argv[]) {
    SDLApplication app("GPU Render");
    app.MainLoop();
    return 0;
}