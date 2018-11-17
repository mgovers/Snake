#ifndef __GAMEMANAGER_H_
#define __GAMEMANAGER_H_

#include "AI.h"
#include "Game.h"

class GameManager
{

public:
  
  GameManager(Game* game_) :
    game(game_) { }

  GameManager(Game* game_, AI* ai_):
  game(game_), ai(ai_) { }

  ~GameManager() {
    delete game;
    delete ai;
  }

  void setGame(Game* newGame);
  void setAI(AI* newAi);
  Game* getGame() const { return this->game; }
  AI* getAI() const { return this->ai; };

  bool doMove(int customMove);
  bool doMove();

  void reset();

private:
  // The current game
  Game* game;

  // The current AI (null if player controlled)
  AI * ai;

};

#endif