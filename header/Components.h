#pragma once
#include "Vec2.h"

class Component{
protected:
  bool hasComponent = false;
};

class CTransform : public Component {
  Vec2 position();
  Vec2 velocity();
};