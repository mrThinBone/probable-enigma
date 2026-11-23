#include <SDL3/SDL.h>
#include "InputComponent.h"
#include "Entity.h"
#include "Commands.h"
#include "Engine/Vec2.h"

namespace{
  const float PIXELS_PER_METER { 10 };
  const float SPEED{5.f * PIXELS_PER_METER};  


  CommandPtr CreateMoveLeftCommand() {
    return std::make_unique<MovementCommand>(
      Vec2{-SPEED, 0.0});
  }

  CommandPtr CreateMoveRightCommand() {
    return std::make_unique<MovementCommand>(
      Vec2{SPEED, 0.0});
  }

  CommandPtr CreateJumpCommand() {
  // Example value in kg*m/s
    const float JUMP_IMPULSE_MAGNITUDE{
      -500.f * PIXELS_PER_METER
    };
    // Return a jump command instead of movement
    return std::make_unique<JumpCommand>(
      Vec2{0.0, JUMP_IMPULSE_MAGNITUDE}
    );
  }
}

void InputComponent::Initialize() {
  BindKeyHeld(SDLK_LEFT, CreateMoveLeftCommand);
  BindKeyHeld(SDLK_RIGHT, CreateMoveRightCommand);
  BindKeyDown(SDLK_SPACE, CreateJumpCommand);
  // Bind other keys...
}

void InputComponent::Tick(float DeltaTime) {
  Entity* owner{GetOwner()};
  if (!owner) return; // Safety check

  // Get the current keyboard state
  const bool* currentKeyStates{ SDL_GetKeyboardState(nullptr) };

  // Check bindings for keys being held down
  for (const auto& [key, factory] : keyHeldBindings) {
    
    SDL_Scancode scancode{ SDL_GetScancodeFromKey(key, nullptr) };
    
    if (currentKeyStates[scancode]) {
      // Key is held, create and handle command
      owner->HandleCommand(factory());
    }
  }
}

void InputComponent::HandleEvent(const SDL_Event& E) {
  if (E.type == SDL_EVENT_KEY_DOWN) {
    Entity* owner{GetOwner()};
    if (!owner) return;
    SDL_Keycode key{E.key.key};
    // if (keyDownBindings.Contains(Key)) {
    if (keyDownBindings.find(key) != keyDownBindings.end()) {

      /*
      Our factory function returns a std::unique_ptr, meaning that the HandleEvent() function should "own" that command. 
      How can it transfer its ownership to the HandleCommand() function without using std::move()?

      The reason is that, in our expression, the compiler can see that our HandleEvent() function is not storing the value 
      returned by KeyDownBindings[Key](). It just immediately forwards it to the HandleCommand() function without storing a local copy. 
      As such, it can be implicitly moved - if HandleEvent() isn't storing the value, it can't use it in the future, 
      so it doesn't need to own it.
      */
      CommandPtr command{keyDownBindings[key]()};
      owner->HandleCommand(std::move(command)); // owner->HandleCommand(keyDownBindings[key]());

      // Alternatively:
      // keyDownBindings[Key]()->Execute(owner);
    }
  }
}