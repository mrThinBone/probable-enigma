#pragma once
#include <iostream>
#include <cmath>
#include <SDL3/SDL.h>

struct Vec2 {
  float x;
  float y;

  float GetLength() const {
    return std::sqrt(x * x + y * y);
  }

  float GetDistance(const Vec2& other) const {
    return std::sqrt(
      std::pow(x - other.x, 2) +
      std::pow(y - other.y, 2)
    );
    
    // alternative:
    // return (*this - other).GetLength();
  }

  Vec2 operator*(float multiplier) const {
    return Vec2{x * multiplier, y * multiplier};
  }

  Vec2 operator/(float divisor) const {
    if (divisor == 0.0f) { return Vec2{0, 0}; }

    return Vec2{x / divisor, y / divisor};
  }

  Vec2& operator*=(float multiplier) {
    x *= multiplier;
    y *= multiplier;
    return *this;
  }

  Vec2& operator/=(float divisor) {
    if (divisor == 0.0f) { return *this; }

    x /= divisor;
    y /= divisor;
    return *this;
  }

  Vec2 operator+(const Vec2& other) const {
    return Vec2{x + other.x, y + other.y};
  }

  Vec2 operator-(const Vec2& other) const {
    return Vec2 {
      x - other.x,
      y - other.y
    };
    
    // Alternative:
    //return *this + (-Other);
  }

  Vec2& operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vec2& operator-=(const Vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
    
    // Alternative:
    //return *this += (-Other);
  }

  Vec2 operator-() const {
    return Vec2{-x, -y};
  }

  Vec2 Normalize() const {
    float length{ GetLength() };

    if (length == 0.0f) { return Vec2{0, 0}; }

    return *this / length;
  }
};

inline Vec2 operator*(float M, const Vec2& V) {
  return V * M;
}

inline std::ostream& operator<<(std::ostream& stream, const Vec2& v) {
  stream << "{ x = " << v.x
    << ", y = " << v.y << " }";
  return stream;
}

// For Float Comparison
bool NearlyEqual(float a, float b,
                 float tolerance = 0.00001) {
  return std::abs(a - b) < tolerance;
}

// For Vec2 Comparison
bool NearlyEqual(const Vec2& a, const Vec2& b,
                 float tolerance = 0.00001) {
  return std::abs(a.x - b.x) < tolerance
    && std::abs(a.y - b.y) < tolerance;
}


SDL_Rect ToSDLRect(const Vec2& pos, int w, int h) {
  return {
    static_cast<int>(std::round(pos.x)),
    static_cast<int>(std::round(pos.y)),
    w, h
  };
}

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

