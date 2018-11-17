#include "GameManager.h"

void GameManager::setGame(Game* newGame)
{
  this->game = newGame;
}

void GameManager::setAI(AI* newAi)
{
  this->ai = newAi;
}

/// <summary> Do a custom (e.g. player-input) move and play it. </summary>
  /// <returns> Whether a valid move was performed. </returns>
bool GameManager::doMove(int customMove)
{
  if (this->game)
    return this->game->step(customMove);
  else
    return false;
}

/// <summary> Let the AI find a move, and then play it. </summary>
  /// <returns> Whether a valid move was performed. </returns>
bool GameManager::doMove() {
  if (this->game && this->ai)
    return this->game->step(this->ai->findMove(*this->game));
  else
    return false;
}

/// <summary> Reset the game </summary>
void GameManager::reset()
{
  this->ai->reset();
  this->game->reset();
}