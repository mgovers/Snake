#include "Game.h"

#include "Body.h"

bool Game::step(const int direction) {
  bool validMove = false;

  GridPos& newHeadPos = body.getNewHeadPos(direction);
  if (testPos(newHeadPos) && testBody(newHeadPos)) {
    validMove = true;
    doMove(direction);
  }

  return validMove;
}

bool Game::testPos(const GridPos& pos) const {
  return (pos.x >= 0 && pos.x < xSize && pos.y >= 0 && pos.y < ySize);
}

bool Game::testBody(const GridPos& pos) const {
  return !(body.inBody(pos));
}

unsigned int Game::getTargetIdx(const GridPos& pos) const  {
  unsigned int targetIdx = targets.size();
  for (unsigned int idx = 0; idx < targets.size(); ++idx) {
    if (pos == targets[idx]) {
      targetIdx = idx;
      break;
    }
  }
  return targetIdx;
}

void Game::doMove(const int direction) {
  unsigned int targetIdx = getTargetIdx(body.getNewHeadPos(direction));
  if (targetIdx != targets.size()) {
    targetMove(direction, targetIdx);
  } else {
    regularMove(direction);
  }
}

void Game::regularMove(const int direction) {
  body.move(direction);
}

void Game::targetMove(const int direction, const unsigned int targetIdx) {
  targets.erase(targets.begin() + targetIdx);
  body.extend(direction);
}

bool Game::addNewTarget(const GridPos& pos) {
  bool success = false;
  if (testPos(pos) && testBody(pos) && getTargetIdx(pos) == targets.size()) {
    targets.push_back(pos);
    success = true;
  }
  return success;
}
