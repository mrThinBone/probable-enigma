#include <iostream>
#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

int main(int argc, char** argv) {
  // A position at (10, 10)
  // w = 1 means it will be affected by translations
  glm::vec3 Position{10.f, 10.f, 1.f};
  
  // A velocity of (5, 2)
  // w = 0 means this vector represents a
  // relative value, and should not be translated
  glm::vec3 Velocity{5.f, 2.f, 0.f};

  // A matrix that translates by (50, 100)
  // Constructed manually using column-major order
  glm::mat3 Translation{
    1.0f, 0.0f, 0.0f,   // Col 0
    0.0f, 1.0f, 0.0f,   // Col 1
    50.0f, 100.0f, 1.0f // Col 2
  };

  // Apply the transformation
  // Important: The matrix is the LEFT operand
  // and the vector is the RIGHT
  glm::vec3 NewPosition{Translation * Position};

  std::cout << "Old Position: "
    << glm::to_string(Position) << "\n";
  std::cout << "New Position: "
    << glm::to_string(NewPosition) << "\n";
    
  // Transform the velocity
  glm::vec3 NewVelocity{Translation * Velocity};

  std::cout << "Old Velocity: "
    << glm::to_string(Velocity) << "\n";
  std::cout << "New Velocity: "
    << glm::to_string(NewVelocity) << "\n";

  return 0;
}