#include <vector>
#include "Scene.h"
#include "Framework/CollisionComponent.h"

void Scene::CheckCollisions() {
  for (size_t i{0}; i < entities.size(); ++i) {
    CollisionComponent* colA{
      entities[i]->GetCollisionComponent()
    };

    // Skip if no collision component
    if (!colA) continue;

    for (size_t j{i + 1}; j < entities.size(); ++j) {
      CollisionComponent* colB{
        entities[j]->GetCollisionComponent()
      };

      // Skip if no collision component
      if (!colB) continue;

      if (colA->IsCollidingWith(*colB)) {
        entities[i]->HandleCollision(*entities[j]);
        entities[j]->HandleCollision(*entities[i]);
        // check for collide response sample
        // https://www.studyplan.dev/sdl3/sdl3-collision-response
      }
    }
  }
}