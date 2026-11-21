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

    // Clamp(velocity);

    std::cout << "\nt = " << time
        << ", Position = " << position;

    std::cout << "\nIntended Speed = "
      << MaximumSpeed
      << ", Actual Speed = "
      << position.GetDistance(previousPosition)
           / deltaTime;

    // simulating Earth-like gravity
    acceleration = {
      0, 9.8f * PIXELS_PER_METER
    };
}

void GameObject::ApplyForce(const Vec2& force) {
    // if 10N of force is applied to an object of mass 5kg, 
    // that object should be accelerated by 10/5 = 2m/s
    acceleration += force / mass;
}