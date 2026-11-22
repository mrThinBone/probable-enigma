#include "Component.h"
#include "Entity.h"
#include "Scene.h"

AssetManager& Component::GetAssetManager() const {
  return owner->GetScene().GetAssetManager();
}