#ifndef __GAME_H__
#define __GAME_H__

#include <vector>

#include "BodyPart.h"

class Game {
 private:
  unsigned int xSize;
  unsigned int ySize;

  std::vector<BodyPart> body;

 public:
  Game() {}
  ~Game() {}

  const std::vector<BodyPart> & getBody() const { return body; }
  bool step(const int xDir, const int yDir) {}
}; // Game

#endif // __GAME_H__

