#include <SDL3/SDL.h>
#include <iostream>
#include "GameObject.h"

void GameObject::Render(SDL_Surface* surface) {
    image.Render(surface, position);
}

void GameObject::Tick(float deltaTime) {
    // https://www.studyplan.dev/sdl3/sdl3-physical-motion

    Vec2 previousPosition{position};

    Vec2 velocity{
      direction.Normalize() * MaximumSpeed
    };
    // Acceleration
    velocity += acceleration * deltaTime;
    
    position += velocity * deltaTime;
    time += deltaTime;

    std::cout << "\nt = " << time
        << ", Position = " << position;

    std::cout << "\nIntended Speed = "
      << MaximumSpeed
      << ", Actual Speed = "
      << position.GetDistance(previousPosition)
           / deltaTime;
}