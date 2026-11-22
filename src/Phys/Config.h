#pragma once

inline constexpr float PIXELS_PER_METER{50.0f};

// For floating-point literals like 10.5_pixels
float operator""_pixels(long double D) {
  return static_cast<float>(D);
}

// For integer literals like 10_pixels
float operator""_pixels(unsigned long long D) {
  return static_cast<float>(D);
}

// For floating-point literals like 2.5_meters
float operator""_meters(long double D) {
  return static_cast<float>(D) * PIXELS_PER_METER;
}

// For integer literals like 2_meters
float operator""_meters(unsigned long long D) {
  return static_cast<float>(D) * PIXELS_PER_METER;
}