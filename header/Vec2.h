#pragma once
#include <ostream>

class Vec2{
  float m_x = 0;
  float m_y = 0;
public:
  Vec2();
  Vec2(float x, float y);
  Vec2(const Vec2& rhs);
  ~Vec2();

  bool operator == (const Vec2& rhs) const;
  bool operator != (const Vec2& rhs) const;

  void operator = (const Vec2& rhs);
  Vec2 operator + (const Vec2& rhs) const;
  Vec2 operator - (const Vec2& rhs) const;
  Vec2 operator * (float rhs) const;
  Vec2 operator / (float rhs) const;

  void operator += (const Vec2& rhs);
  void operator -= (const Vec2& rhs);
  void operator *= (float rhs);
  void operator /= (float rhs);

  friend std::ostream& operator << (std::ostream& os, const Vec2& rhs);

  float length() const;
  bool normalize();
  float distance(const Vec2& rhs) const;
};
