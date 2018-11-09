#ifndef __GAME_H__
#define __GAME_H__

#include <vector>

#include "Body.h"

class Game {
 private:
  unsigned int xSize;
	 unsigned int ySize;

  Body body;

 public:
  Game() {}
  ~Game() {}

  const Body & getBody() const { return *&body; }
  bool step(const int direction);
}; // Game

#endif // __GAME_H__
