#pragma once
#include "myVec.h"
#include "SFML/Graphics.hpp"

class Position{
  myVec m_position = {0.0f, 0.0f};
public:
  Position() = default;
  Position(const myVec& position) : m_position(position) {}
  ~Position() = default;

  friend std::ostream& operator << (std::ostream& os, const Position& rhs) {
    os << "Position: " << rhs.m_position << std::endl;
    return os;
  }
};

class Velocity{
  myVec m_velocity = {0.0f, 0.0f};
public:
  Velocity() = default;
  Velocity(const myVec& velocity) : m_velocity(velocity) {}
  ~Velocity() = default;

  friend std::ostream& operator << (std::ostream& os, const Velocity& rhs) {
    os << "Velocity: " << rhs.m_velocity << std::endl;
    return os;
  }
};

class BoundingBox{
  myVec m_bBox = {0.0f, 0.0f};
  sf::RectangleShape m_boundingBox;
public:
  BoundingBox() = default;
  explicit BoundingBox(myVec&  bBox) : m_boundingBox(sf::Vector2f(m_bBox.getX(), m_bBox.getY())) {}
  ~BoundingBox() = default;

  friend std::ostream& operator << (std::ostream& os, const BoundingBox& rhs) {
    os << "(" << rhs.m_bBox.getX() << "," << rhs.m_bBox.getY() << ")" << std::endl;
    return os;
  }
};

class Shape {
public:
  sf::RectangleShape m_shape;
  Shape(const float shapeW, const float shapeH) : m_shape(sf::Vector2f(shapeW, shapeH)) {
    m_shape.setFillColor(sf::Color::Blue);
    m_shape.setPosition(100, 100);
  }
};