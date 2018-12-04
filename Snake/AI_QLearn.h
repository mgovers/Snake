#ifndef _AI_QLEARN_H_
#define _AI_QLEARN_H_

#include <Eigen/Dense>

#include "AI.h"
#include "Game.h"
#include <Network.h>

class AI_QLearn : public AI
{
public:
  int findMove(Game& game);
  void reset();
};

#endif