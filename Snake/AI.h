#ifndef _AI_H_
#define _AI_H_

class Game;
class AI
{
	public:

  // Virtual function that returns the optimal move given a game
	virtual int findMove(Game &game) = 0;
};

#endif