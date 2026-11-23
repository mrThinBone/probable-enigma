#include "Commands.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"

void StaticMovementCommand::Execute(Entity* T) {
    if (!T) return; // Safety check
    std::cout << "\nMoving: " << movement;
    target = T;
    target->GetTransformComponent()->Move(movement);
}

void StaticMovementCommand::Undo() {
    if (!target) return; // Safety check
    target->GetTransformComponent()->Move(-movement);
}

void MovementCommand::Execute(Entity* target) {
  if (!target) return;  // Safety Check
  
  PhysicsComponent* physics{ target->GetPhysicsComponent() };
  
  if (physics) {
    physics->SetVelocity({ velocity.x, physics->GetVelocity().y });
  } else {
    std::cerr << "Error: MovementCommand "
      "requires a PhysicsComponent on entity\n";
  }
}

void JumpCommand::Execute(Entity* target) {
  if (!target) return;  // Safety Check

  PhysicsComponent* physics{ target->GetPhysicsComponent() };
  
  if (physics) {
    physics->ApplyImpulse(impulse);
  } else {
    std::cerr << "Error: JumpCommand "
      "requires a PhysicsComponent on entity\n";
  }
}