#include "maze.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

SquareMaze::SquareMaze()
{
  //do nothign
}

void SquareMaze::makeMaze(int width, int height)
{
  width_=width;
  height_=height;

  mazeWalls=vector<vector<vector<bool>>>(width);
  for (int x=0;x<width;x++)
  {
    mazeWalls[x]=vector<vector<bool>>(height);
    for (int y=0;y<height;y++)
    {
      mazeWalls[x][y]=vector<bool>(2);
      mazeWalls[x][y][0]=true; /////RIGHT
      mazeWalls[x][y][1]=true;  //////DOWN
    }
  }

  //get rid of some walls now
  DisjointSets dset;
  dset.addelements(width*height);
  int tot=width*height;
  while (tot>1)
  {
    int y=rand()%height;
    int x=rand()%width_;
    int dir=rand()%2;
    if (mazeWalls[x][y][dir])
    {
      if (dir==1)//DOWN
      {
        if (y<height-1)
        {
          int chk1=(x+width*y);
          int chk2=(width*(1+y)+x);
          if (dset.find(chk1)!=dset.find(chk2))
          {
            tot=tot-1;
            dset.setunion(chk1,chk2);//combine em
            mazeWalls[x][y][1]=false;
          }
        }
      }
      else //right
      {
        {
          if (x<width_-1)
          {
            int chk1=(x+(width*y));
            int chk2=(y*width+x+1);
            if (dset.find(chk1)!=dset.find(chk2))
            {
              tot=tot-1;
              dset.setunion(chk1,chk2);//combine em
              mazeWalls[x][y][0]=false;
            }
           }
        }
      }

    }
  }
}
//0 right 1 down 2 left 3 up
bool SquareMaze::canTravel(int x,int y, int dir) const
{
  if (x<0 || x>=width_ || y<0 ||y>=height_)return false;
  if (dir==0 && (x+1)<width_ && !mazeWalls[x][y][0])return true;//RIGHT
  else if (dir==1 && (y+1)<height_ && !mazeWalls[x][y][1])return true;//DOWN
  else if (dir==2 && (x-1)>=0 && !mazeWalls[x-1][y][0])return true;//left
  else if (dir==3 && (y-1)>=0 && !mazeWalls[x][y-1][1])return true;//UP
  else return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
  if (x<0 || x>=width_ || y<0 ||y>=height_)return;
  else mazeWalls[x][x][dir]=exists;
}

vector<int> SquareMaze::solveMaze()
{
  distancemap=vector<int>(width_*height_);
  visitedmap=vector<bool>(width_*height_);
  for (int i=0;i<width_*height_;i++)
  {
    distancemap[i]=-1;
    visitedmap[i]=false;
  }
  fillmap(0,0,0);
  int maxloc=0;
  for (int x=0;x<width_;x++)
  {
    if (maxloc<distancemap[(height_-1)*width_+x])
    {
      maxloc=(height_-1)*width_+x;
      int destx=x;
    }
  }
int desty=height_-1;
//have dest x and dest y now jsut need to find path

return vector<int>();
}

void SquareMaze::fillmap(int x,int y, int steps)
{
  if (visitedmap[y*width_+x])return;
  distancemap[y*width_+x]=steps;
  visitedmap[y*width_+x]=true;
  if (canTravel(x,y,0))fillmap(x+1,y,steps+1);
  if (canTravel(x,y,1))fillmap(x,y+1,steps+1);
  if (canTravel(x,y,2))fillmap(x-1,y,steps+1);
  if (canTravel(x,y,3))fillmap(x,y-1,steps+1);
  return;


}

PNG * SquareMaze::drawMaze() const
{
  PNG * adf=new PNG();
  return adf;
}

PNG * SquareMaze::drawMazeWithSolution()
{
  PNG * adf=new PNG();
  return adf;
}
