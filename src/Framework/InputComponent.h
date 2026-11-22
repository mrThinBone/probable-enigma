#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include <SDL3/SDL.h>
#include "Component.h"

class Command;

using CommandPtr = std::unique_ptr<Command>;
using CommandFactory = std::function<CommandPtr()>;
using KeyToFactoryMap = std::unordered_map<SDL_Keycode, CommandFactory>;

class InputComponent : public Component {
 public:
  using Component::Component;
  void Initialize() override;
  void Tick(float deltaTime) override;
  void HandleEvent(const SDL_Event& E) override;

  void BindKeyDown(SDL_Keycode key, CommandFactory factory) {
    keyDownBindings[key] = factory;
  }

  void BindKeyHeld(SDL_Keycode key, CommandFactory factory) {
    keyHeldBindings[key] = factory;
  }

private:
  // Map for discrete key presses (events)
  KeyToFactoryMap keyDownBindings;
  // Map for continuous key holds (polling)
  KeyToFactoryMap keyHeldBindings;
};