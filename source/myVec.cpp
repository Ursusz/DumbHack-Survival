#include "myVec.h"

#include <cmath>
#include <iostream>
#include <ostream>

myVec::myVec() = default;

myVec::myVec(float x, float y)
    :m_x(x), m_y(y)
{}

myVec::myVec(const myVec& rhs) {
    m_x = rhs.m_x;
    m_y = rhs.m_y;
}

myVec::~myVec() {}


bool myVec::operator == (const myVec& rhs) const{
    return m_x == rhs.m_x && m_y == rhs.m_y;
}

bool myVec::operator != (const myVec& rhs) const{
    return m_x != rhs.m_y || m_y != rhs.m_y;
}

void myVec::operator = (const myVec& rhs) {
    m_x = rhs.m_x;
    m_y = rhs.m_y;
}

myVec myVec::operator + (const myVec& rhs) const{
  return {m_x + rhs.m_x, m_y + rhs.m_y};
}

myVec myVec::operator - (const myVec& rhs) const {
    return {m_x - rhs.m_x, m_y - rhs.m_y};
}

myVec myVec::operator * (float rhs) const {
    return {m_x * rhs, m_y * rhs};
}

myVec myVec::operator / (float rhs) const {
    return {m_x / rhs, m_y / rhs};
}

void myVec::operator += (const myVec& rhs) {
    m_x += rhs.m_x;
    m_y += rhs.m_y;
}

void myVec::operator -= (const myVec& rhs) {
    m_x -= rhs.m_x;
    m_y -= rhs.m_y;
}

void myVec::operator *= (float rhs) {
    m_x *= rhs;
    m_y *= rhs;
}

void myVec::operator /= (float rhs) {
    m_x /= rhs;
    m_y /= rhs;
}

float myVec::length() const {
    return sqrt(m_x * m_x + m_y * m_y);
}

bool myVec::normalize() {
    const float len = length();
    if(len == 0.0f) {
        std::cerr << "Vec2 normalize() called with zero length" << std::endl;
        return false;
    }
    m_x /= len;
    m_y /= len;
    return true;
}

float myVec::distance(const myVec& rhs) const {
    return (rhs - *this).length();
}

std::ostream& operator << (std::ostream& os, const myVec& rhs) {
    os << "(" << rhs.m_x << ", " << rhs.m_y << ")";
    return os;
}

float myVec::getX() const { return m_x; }
float myVec::getY() const { return m_y; }