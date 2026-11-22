#pragma once
#include <memory>
#include <vector>
#include <SDL3/SDL.h>
#include "Component.h"
#include "TransformComponent.h"
#include "ImageComponent.h"
#include "Commands.h"

using ComponentPtr = std::unique_ptr<Component>;
using ComponentPtrs = std::vector<ComponentPtr>;

using ImageComponents = std::vector<ImageComponent*>;

class Scene;

class Entity {
public:
  Entity(Scene& scene) : owningScene{&scene} {}
  
  Scene& GetScene() const { return *owningScene; }

  virtual void HandleEvent(const SDL_Event& E) {
    for (ComponentPtr& C : components) {
      C->HandleEvent(E);
    }
  }

  virtual void Tick(float DeltaTime) {
    for (ComponentPtr& C : components) {
      C->Tick(DeltaTime);
    }
  }

  virtual void Render(SDL_Surface* Surface) {
    for (ComponentPtr& C : components) {
      C->Render(Surface);
    }
  }

  virtual ~Entity() = default;

  virtual void HandleCommand(std::unique_ptr<Command> cmd) {
    cmd->Execute(this);
  }

  TransformComponent* AddTransformComponent() {
    if (GetTransformComponent()) {
      std::cout << "Error: Cannot have "
        "multiple transform components";
      return nullptr;
    }

    // Add a new TransformComponent, emplace_back()
    // constructs it in place and returns a
    // reference to the added element
    ComponentPtr& newComponent{
      components.emplace_back(
        std::make_unique<TransformComponent>(this)
      )
    };

    // Convert the ComponentPtr ie 
    // std::unique_ptr<Component> to the
    // the return type: a TransformComponent* 
    return static_cast<TransformComponent*>(
      newComponent.get()
    );
  }

  TransformComponent* GetTransformComponent() const {
    for (const ComponentPtr& C : components) {
      // Try to cast the base Component pointer
      // to a TransformComponent pointer
      if (auto ptr{dynamic_cast<TransformComponent*>(C.get())}) {
        // Cast successful, we found it!
        return ptr;
      }
    }

    // Went through all components, didn't
    // find a transform component
    return nullptr;
  }

  ImageComponent* AddImageComponent(const std::string& filePath) {
    ComponentPtr& newComponent{
      components.emplace_back(
        std::make_unique<ImageComponent>(this, filePath)
      )
    };

    newComponent->Initialize(); 

    return static_cast<ImageComponent*>(
      newComponent.get()
    );
  }

  ImageComponents GetImageComponents() const {
    ImageComponents result;
    for (const ComponentPtr& C : components) {
      // Try to cast to ImageComponent*
      if (auto ptr{dynamic_cast<
        ImageComponent*>(C.get())}
      ) {
        // If successful, add it to our
        // result vector
        result.push_back(ptr);
      }
    }
    return result;
  }

  void RemoveComponent(Component* PtrToRemove) {
    // Iterate through the vector to find
    // the component to remove
    for (size_t i{0}; i < components.size(); ++i) {
      // Check if the raw pointer managed by
      // the unique_ptr matches
      if (components[i].get() == PtrToRemove) {
        // Found it! Erase the element at this index.
        // components.begin() + i gives an iterator
        // to the element.
        components.erase(components.begin() + i);
        // Assuming only one component matches,
        // so we can stop searching
        return;
      }
    }
    // If the loop finishes, the component
    // wasn't found
    std::cout << "Warning: Attempted to remove "
      "a component not found on this entity.\n";
  }

private:
  ComponentPtrs components;
  Scene* owningScene;
};