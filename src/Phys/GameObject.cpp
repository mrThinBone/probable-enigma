#include <SDL3/SDL.h>
#include <iostream>
#include "GameObject.h"

void GameObject::HandleEvent(SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_SPACE) {
            // Jumping: Apply upward impulse
            // remember, positive Y means fall down
            ApplyImpulse({0.0f, -15000.0f});
        }
    } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            ApplyPositionalImpulse(
                Vec2{event.button.x, event.button.y},
                10000.0f
            );
        }
    }
}

void GameObject::Render(SDL_Surface* surface) {

    // if (!IsInViewport()) return;

    image.Render(surface, position);
#ifdef DRAW_DEBUG_HELPERS
    // SDL_Rect positionIndicator{
    //     int(position.x) - 10, int(position.y) - 10, 20, 20};

    // SDL_FillSurfaceRect(
    //     trajectories,
    //     &positionIndicator,
    //     SDL_MapRGB(
    //     SDL_GetPixelFormatDetails(trajectories->format),
    //     nullptr, 220, 0, 0
    //     )
    // );

    // SDL_BlitSurface(
    //     trajectories, nullptr,
    //     surface, nullptr);

    bounds.Render(surface);
#endif
}

void GameObject::Tick(float deltaTime) {
    if (!isMovable) return;

    CalculateAnimation();

    if (scene.GetPlayerCharacter().GetPosition().GetDistance(position) > 20.0f * PIXELS_PER_METER) {
        std::cout << "Skipping Physics\n";
        return;
    }
    std::cout << "Calculating Physics\n";

    // Run physics calculations...

    ApplyForce(GetFrictionForce(deltaTime));
    ApplyForce(GetDragForce());

    // Apply the timed force if active
    if (forceTimeRemaining > 0) {
        ApplyForce({10000, 0});
        forceTimeRemaining -= deltaTime;
    }

    // https://www.studyplan.dev/sdl3/sdl3-physical-motion

    Vec2 previousPosition{position};

    //Vec2 velocity{
    //  direction.Normalize() * MaximumSpeed
    //};
    // Acceleration
    velocity += acceleration * deltaTime;
    
    position += velocity * deltaTime;
    time += deltaTime;

    Clamp(velocity);

    bounds.SetPosition(position);

    HandleCollisions();

    std::cout << "\nt = " << time
        << ", Position = " << position;

    std::cout 
        << "Actual Speed = "
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

void GameObject::CalculateAnimation() {
    SDL_Rect boundingBoxRect{BoundingBox::Round(
        bounds.GetRect()
    )};
    
    SDL_Rect viewportRect{scene.GetViewport()};

    if (!SDL_HasRectIntersection(&viewportRect, &boundingBoxRect)) {
        std::cout << "Not visible - skipping\n";
        return;
    }

    std::cout << "Calculating animation\n";
    // ....
}

void GameObject::HandleCollisions() {
    isOnGround = false;
    for (const GameObjectPtr& object : scene.GetObjects()) {
        if (object.get() == this) continue;

        SDL_FRect intersection;
        if (bounds.GetIntersection(object->bounds, &intersection)) {
            object->OnHit(*this);
            if (object->CanPassThrough()) {
                continue;
            }

            if (object->HasType(GameObjectType::Floor)) {
                isOnGround = true;
                position.y -= intersection.h;
                velocity.y = 0;
            }
        }
    }
}