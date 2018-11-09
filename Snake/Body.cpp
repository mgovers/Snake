#include "Body.h"

Body::Body(const int& x0 = 0, const int& y0 = 0, const int& dir0 = 0, const unsigned int& initialSize = 3) {
  direction = dir0;
  body.push_back(BodyPart{ x0, y0 });
  head = 0;
  headIt = body.begin();

  for (unsigned int i = 0; i < initialSize; ++i) {
    extend(direction);
  }
}

const BodyPart& Body::operator[](unsigned int idx) const {
  return body[idx];
}

BodyPart& Body::operator[](unsigned int idx) {
  return body[idx];
}

bool Body::move(const int direction) {
  updateHead();

  GridPos newHeadPos = getNewHeadPos(direction);
  body[head].x = newHeadPos.x;
  body[head].y = newHeadPos.y;
}

void Body::extend(const int direction) {
  GridPos newHeadPos = getNewHeadPos(direction);
  body.insert(headIt, BodyPart{ newHeadPos.x, newHeadPos.y } );
}

GridPos Body::getNewHeadPos(const int direction) const {
  const auto& curHeadPos = body[head];
  GridPos newHeadPos = { curHeadPos.x, curHeadPos.y };

  switch (direction) {
  case 0: { ++newHeadPos.x; break; }
  case 1: { ++newHeadPos.y; break; }
  case 2: { --newHeadPos.x; break; }
  case 3: { --newHeadPos.y; break; }
  default: { } // nothing happens
  }
  
  return newHeadPos;
}

void Body::updateHead() {
  if (head > 0) {
    --head;
    --headIt;
  } else {
    head   = body.size() - 1;
    headIt = body.end() - 1;
  }
}