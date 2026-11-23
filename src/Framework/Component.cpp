#include "Component.h"
#include "Entity.h"
#include "Context.h"

Context& Component::GetContext() const {
  return owner->GetContext();
}

AssetManager& Component::GetAssetManager() const {
  return owner->GetContext().assets;
}

Vec2 Component::GetOwnerPosition() const {
  TransformComponent* transform{ GetOwner()->GetTransformComponent() };

  if (!transform) {
    std::cerr << "Error: attempted to get position"
      " of an entity with no transform component\n";
    return {0, 0};
  }
  
  return transform->GetPosition();
}

float Component::GetOwnerScale() const {
  TransformComponent* transform{ GetOwner()->GetTransformComponent() };
  if (!transform) {
    std::cerr << "Error: attempted to get scale"
      " of an entity with no transform component\n";
    return 1.0;
  }
  return transform->GetScale();
}