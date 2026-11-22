#include "Engine/Vec2.h"

class Character {
public:
  Vec2 position { 2.0, 6.0 };
  float movementSpeed { 3.0 };
  
  void Move(const Vec2& movement) {
    // If the distance indicated by the Movement vector is shorter 
    // than the Character's maximum movement speed, 
    // they will move too far and overshoot the intended destination.
    // To prevent this, check if we can move immediately.
    if (movement.GetLength() <= movementSpeed) {
      position += movement;
      return;
    }
  
    Vec2 direction{movement.Normalize()};
    Vec2 constrainedMovement{direction * movementSpeed};
    position += constrainedMovement;
  }

  void MoveTowards(const Character& target) {
    Move(target.position - position);
  }

  void MoveAway(const Character& target) {
    Move(position - target.position);
  }
};