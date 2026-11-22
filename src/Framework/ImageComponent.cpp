#include <iostream>
#include "ImageComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

#include <iostream>
#include "ImageComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

void ImageComponent::Render(SDL_Surface* surface) {
  TransformComponent* transform{
    GetOwner()->GetTransformComponent()
  };

  std::cout << "ImageComponent rendering at: "
    << transform->GetPosition() << '\n';
}

void ImageComponent::Initialize() {
  Entity* owner{GetOwner()};
  if (!owner->GetTransformComponent()) {
    std::cout << "Error: ImageComponent requires"
      " TransformComponent on its Owner\n";

    owner->RemoveComponent(this);
  }
}