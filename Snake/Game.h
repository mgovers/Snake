#ifndef __GAME_H__
#define __GAME_H__

#include <vector>

#include "Body.h"

class Game {
 private:
  unsigned int xSize=0;
	unsigned int ySize=0;

  // The snake body
  Body body;
  // The food pieces
  std::vector<GridPos> targets;

  unsigned int getTargetIdx(const GridPos& pos) const;

  void Game::doMove(const int direction);
  void Game::regularMove(const int direction);
  void Game::targetMove(const int direction, const unsigned int targetIdx);

 public:
  Game(const unsigned int xSize_, const unsigned int ySize_) :
    xSize(xSize_), ySize(ySize_) {}

  enum AITYPE
  {
    EASY = 0
  };

  const Body&                 getBody   () const { return *&body;    }
  const std::vector<GridPos>& getTargets() const { return *&targets; }

  int computeAIMove();
  bool step(const int direction);
  bool addNewTarget(const GridPos& pos);
  void getSize(unsigned int& sizeX, unsigned int &sizeY);
  unsigned int getXSize();
  unsigned int getYSize();
  bool testPos(const GridPos& pos) const;
  bool testBody(const GridPos& pos) const;
  bool testEmpty(const GridPos &pos) const;
  void reset();

}; // Game

#endif // __GAME_H__
