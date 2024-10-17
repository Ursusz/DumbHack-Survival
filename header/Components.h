#pragma once
#include "myVec.h"

class Component{
protected:
  bool hasComponent = false;
};

class CTransform : public Component {
  myVec position();
  myVec velocity();
};