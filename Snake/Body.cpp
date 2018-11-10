#include "Body.h"

bool operator==(const GridPos& pos1, const GridPos& pos2) { return (pos1.x == pos2.x && pos1.y == pos2.y); }

Body::Body(const GridPos& initialPos, const int& initialDirection, const unsigned int& initialSize) {
  direction = initialDirection;
  body.push_back(BodyPart{ initialPos.x, initialPos.y });
  head = 0;

  for (unsigned int i = 0; i < initialSize; ++i) {
    extend(direction);
  }
}

const BodyPart& Body::operator[](unsigned int idx) const {
  return body[(head + idx) % body.size()];
}

BodyPart& Body::operator[](unsigned int idx) {
  return body[(head + idx) % body.size()];
}

void Body::move(const int direction) {
  updateHead();

  GridPos newHeadPos = getNewHeadPos(direction);
  body[head].x = newHeadPos.x;
  body[head].y = newHeadPos.y;
}

void Body::extend(const int direction) {
  GridPos newHeadPos = getNewHeadPos(direction);
  body.insert(body.begin() + head, BodyPart{ newHeadPos.x, newHeadPos.y } );
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

bool Body::inBody(const GridPos& pos) const {
  bool found = false;
  for (auto& bodyPart : body) {
    if (pos == bodyPart) {
      found = true;
      break;
    }
  }
  return found;
}

void Body::updateHead() {
  if (head > 0) {
    --head;
  } else {
    head = body.size() - 1;
  }
}
