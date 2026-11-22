#pragma once
#include "Engine/Vec2.h"

class Entity;

class Command {
public:
  virtual void Execute(Entity* Target){};
  virtual ~Command() = default;
};

class MovementCommand : public Command {
public:
  MovementCommand(Vec2 movement): movement{movement} {}
  void Execute(Entity* T) override;

  void Undo();
  
  Vec2 movement;
  Entity* target;
};