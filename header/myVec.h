#pragma once
#include <ostream>
#include <utility>
#include <sstream>
#include <string>

#include "../header/Exceptions.h"

class myVec{
  float m_x = 0;
  float m_y = 0;
public:
  myVec();
  myVec(float x, float y);
  myVec(const myVec& rhs);
  ~myVec();

  bool operator == (const myVec& rhs) const;
  bool operator != (const myVec& rhs) const;

  myVec& operator = (const myVec& rhs);
  myVec operator + (const myVec& rhs) const;
  myVec operator - (const myVec& rhs) const;
  myVec operator * (float rhs) const;
  myVec operator / (float rhs) const;

  void operator += (const myVec& rhs);
  void operator -= (const myVec& rhs);
  void operator *= (float rhs);
  void operator /= (float rhs);

  friend std::ostream& operator << (std::ostream& os, const myVec& rhs);

  [[nodiscard]]
  float length() const;

  bool normalize();

  [[nodiscard]]
  float distance(const myVec& rhs) const;

  [[nodiscard]]
  float getX() const;
  [[nodiscard]]
  float getY() const;

  std::string myVec_to_string() const;

  friend void swap(myVec& v1, myVec& v2) noexcept;
};
