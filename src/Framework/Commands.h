#pragma once
#include "Engine/Vec2.h"

class Entity;

class Command {
public:
  virtual void Execute(Entity* Target){};
  virtual ~Command() = default;
};

class StaticMovementCommand : public Command {
public:
  StaticMovementCommand(Vec2 movement): movement{movement} {}
  void Execute(Entity* T) override;

  void Undo();
  
  Vec2 movement;
  Entity* target;
};

class MovementCommand : public Command {
public:
  MovementCommand(Vec2 velocity): velocity{velocity} {}
  void Execute(Entity* T) override;

  Vec2 velocity;
  Entity* target;
};

class JumpCommand : public Command {
 public:
  JumpCommand(Vec2 impulse) : impulse(impulse) {}
  void Execute(Entity* target) override;
  Vec2 impulse;
};