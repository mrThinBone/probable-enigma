#include "Component.h"
#include "Entity.h"
#include "Context.h"

AssetManager& Component::GetAssetManager() const {
  return owner->GetContext().assets;
}
