#include "Commands.h"
#include "Entity.h"
#include "TransformComponent.h"

void MovementCommand::Execute(Entity* T) {
    if (!T) return; // Safety check
    std::cout << "\nMoving: " << movement;
    target = T;
    target->GetTransformComponent()->Move(movement);
}

void MovementCommand::Undo() {
    if (!target) return; // Safety check
    target->GetTransformComponent()->Move(-movement);
}