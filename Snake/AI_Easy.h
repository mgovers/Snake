#ifndef _AI_EASY_H_
#define _AI_EASY_H_

#include <vector>

#include "AI.h"
#include "Game.h"

class AI_Easy : public AI
{
public:
  int findMove(Game& game);
  void reset();

private:    
  std::vector<std::vector<int>> AI_Easy::createScentMap(Game &game);
};


#endif