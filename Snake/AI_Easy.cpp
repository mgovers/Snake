#include "AI_Easy.h"
#include <algorithm>
#include <iostream>

void AI_Easy::reset() 
{
  // This AI has no memory and does not need to be reset
}

/// <summary>
/// Returns the empty neighbors of the provided grid position. 4-connectivity.
/// Additionally, its value of occupiedMap must be zero.
/// </summary>
std::vector<GridPos> getValidNeighbors(Game &game, std::vector<std::vector<int>> occupiedMap, GridPos pos)
{
  std::vector<GridPos> output;
  if (game.testEmpty({ pos.x + 1, pos.y }) && occupiedMap[pos.x+1][pos.y]==0)
    output.push_back({ pos.x + 1, pos.y });
  if (game.testEmpty({ pos.x, pos.y - 1  }) && occupiedMap[pos.x][ pos.y - 1] == 0)
    output.push_back({ pos.x, pos.y - 1 });
  if (game.testEmpty({ pos.x - 1, pos.y }) && occupiedMap[pos.x - 1][ pos.y] == 0)
    output.push_back({ pos.x - 1, pos.y });
  if (game.testEmpty({ pos.x, pos.y + 1 }) && occupiedMap[pos.x][ pos.y + 1] == 0)
    output.push_back({ pos.x, pos.y + 1 });

  return output;
}

/// <summary>
/// Returns the empty neighbors of the provided grid position. 4-connectivity.
/// </summary>
std::vector<GridPos> getValidNeighbors(Game &game, GridPos pos)
{
  std::vector<GridPos> output;
  if (game.testEmpty({ pos.x + 1, pos.y }))
    output.push_back({ pos.x + 1, pos.y });
  if (game.testEmpty({ pos.x, pos.y - 1 }))
    output.push_back({ pos.x, pos.y - 1 });
  if (game.testEmpty({ pos.x - 1, pos.y }))
    output.push_back({ pos.x - 1, pos.y });
  if (game.testEmpty({ pos.x, pos.y + 1 }))
    output.push_back({ pos.x, pos.y + 1 });

  return output;
}

int positionToDirection(const GridPos &src, const GridPos &dst)
{
  if (dst.x == src.x + 1 && dst.y == src.y)
    return 0;
  else if (dst.x == src.x && dst.y == src.y - 1)
    return 1;
  else if (dst.x == src.x - 1 && dst.y == src.y)
    return 2;
  else if (dst.x == src.x && dst.y == src.y + 1)
    return 3;
  else // Invalid
    return -1;
}

/// <summary>
/// Creates a scent map of the size of the grid.
/// A scent map is a grid of ints >=0 with maximum value at target locations,
/// and decreasing from there.
/// </summary>
std::vector<std::vector<int>> AI_Easy::createScentMap(Game &game)
{
  // Allocate a grid
  std::vector<std::vector<int>> scentMap;
  for (unsigned int i = 0; i < game.getXSize(); i++)
  {
    auto column = std::vector<int>(game.getYSize());
    scentMap.push_back(column);
  }

  const unsigned int maxScent = game.getXSize() * game.getYSize();

  // Fill the grid

  //todo edge case of two adjacent foods
  std::vector<GridPos> coords;
  for (unsigned int i = 0; i < game.getTargets().size(); i++) {
    scentMap[game.getTargets()[i].x][game.getTargets()[i].y] = maxScent;
    auto candidates = getValidNeighbors(game, scentMap, game.getTargets()[i]);
    coords.insert(coords.end(), candidates.begin(), candidates.end());     
  }
  
  while (coords.size() > 0)
  {   
    // Get all neighbors
    auto neighbors = getValidNeighbors(game, coords[0]);

    // Assign scent to the current square
    std::vector<int> scentOptions;
    for each (GridPos pos in neighbors)
    {
      scentOptions.push_back(scentMap[pos.x][pos.y]);
    }
    scentMap[coords[0].x][coords[0].y] = *std::max_element(scentOptions.begin(),scentOptions.end()) - 1;
    
    // Add the unassigned neighbors to the queue
    auto candidates = getValidNeighbors(game, scentMap, coords[0]);
    for each (GridPos pos in candidates)
    {
      // Unique insert (slow but steady)
      if (std::find(coords.begin(), coords.end(), pos) == coords.end())
        coords.push_back(pos);
    }
    //coords.insert(coords.end(), candidates.begin(), candidates.end());
    // Eras the current pos from the queue
    coords.erase(coords.begin());
  }

  return scentMap;

}

void DEBUGplotScent(std::vector<std::vector<int>> scentMap)
{
  if (scentMap.size() == 0)
    return;
  // Scent is stored column-wise...
  for (unsigned int j = 0; j < scentMap[0].size(); j++) {
    for (unsigned int i = 0; i < scentMap.size(); i++) {
      std::cout << scentMap[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int AI_Easy::findMove(Game& game)
{
  //
  // 1. Compute the scent map
  //
  auto scentMap = createScentMap(game);

  //DEBUGplotScent(scentMap);

  //
  // 2. Get the valid moves and their scents
  //
  std::vector<GridPos> candidates = getValidNeighbors(game, game.getBody()[0]);
  std::vector<int> candidateScents;
  for (unsigned int i = 0; i < candidates.size(); i++)
    candidateScents.push_back( scentMap[candidates[i].x][candidates[i].y] );
  if (candidates.size() == 0)
  {
    // No valid move, game over! 
    // To Do: give error response
    return 0;
  }

  //
  // 3. Do the move with maximum scent
  // (If this move has positive scent, you are guaranteed to be able to reach the current target,
  // but you might get stuck for the next target. Hence, Easy AI.)
  //
  auto maxElement = std::max_element(candidateScents.begin(), candidateScents.end());
  auto maxIdx = std::distance(candidateScents.begin(), maxElement);
  // Convert the next square into a direction
  return positionToDirection(game.getBody()[0],candidates[maxIdx]);

}