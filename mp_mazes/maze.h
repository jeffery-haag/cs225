#ifndef _MAZE_H_
#define _MAZE_H_

#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <vector>


using namespace std;
using namespace cs225;

class SquareMaze
{
public:
  SquareMaze();
  void makeMaze(int width,int height);
  bool canTravel(int x, int y, int dir) const;
  void setWall(int x, int y, int dir, bool exists);
  vector<int> solveMaze();
  PNG * drawMaze() const;
  PNG * drawMazeWithSolution();
  void fillmap(int x,int y, int steps);

//  PNG * drawMaze_Creative()
private:
  int width_;
  int height_;
  vector<vector<vector<bool>>> mazeWalls;
  vector<int> distancemap;
  vector<bool> visitedmap;

};
#endif
