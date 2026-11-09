#pragma once

enum MovementDirection { Up, Down, Left, Right };

struct SnakeData {
  int headRow;
  int headCol;
  int length;
  MovementDirection direction;
};