#include "Vec2.h"

#include <cmath>
#include <iostream>
#include <ostream>

Vec2::Vec2() = default;

Vec2::Vec2(float x, float y)
    :m_x(x), m_y(y)
{}

Vec2::Vec2(const Vec2& rhs) {
    m_x = rhs.m_x;
    m_y = rhs.m_y;
}

Vec2::~Vec2() = default;


bool Vec2::operator == (const Vec2& rhs) const{
    return m_x == rhs.m_x && m_y == rhs.m_y;
}

bool Vec2::operator != (const Vec2& rhs) const{
    return m_x != rhs.m_y || m_y != rhs.m_y;
}

void Vec2::operator = (const Vec2& rhs) {
    m_x = rhs.m_x;
    m_y = rhs.m_y;
}

Vec2 Vec2::operator + (const Vec2& rhs) const{
  return {m_x + rhs.m_x, m_y + rhs.m_y};
}

Vec2 Vec2::operator - (const Vec2& rhs) const {
    return {m_x - rhs.m_x, m_y - rhs.m_y};
}

Vec2 Vec2::operator * (float rhs) const {
    return {m_x * rhs, m_y * rhs};
}

Vec2 Vec2::operator / (float rhs) const {
    return {m_x / rhs, m_y / rhs};
}

void Vec2::operator += (const Vec2& rhs) {
    m_x += rhs.m_x;
    m_y += rhs.m_y;
}

void Vec2::operator -= (const Vec2& rhs) {
    m_x -= rhs.m_x;
    m_y -= rhs.m_y;
}

void Vec2::operator *= (float rhs) {
    m_x *= rhs;
    m_y *= rhs;
}

void Vec2::operator /= (float rhs) {
    m_x /= rhs;
    m_y /= rhs;
}

float Vec2::length() const {
    return sqrt(m_x * m_x + m_y * m_y);
}

bool Vec2::normalize() {
    const float len = length();
    if(len == 0.0f) {
        std::cerr << "Vec2 normalize() called with zero length" << std::endl;
        return false;
    }
    m_x /= len;
    m_y /= len;
    return true;
}

float Vec2::distance(const Vec2& rhs) const {
    return (rhs - *this).length();
}

std::ostream& operator << (std::ostream& os, const Vec2& rhs) {
    os << "(" << rhs.m_x << ", " << rhs.m_y << ")";
    return os;
}