#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance)
{
  tol=tolerance;
  begins=start;
  //queue<Point&> nextup_=new queue<Point&>
  image=PNG(png);
  int a=1;
  this->add(begins);
  bool failsafe;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this->image,this->begins,this->tol,this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end()
{
  /** @todo [Part 1] */
//  return ImageTraversal::Iterator();
  ImageTraversal::Iterator newb=ImageTraversal::Iterator(this->image,this->begins,this->tol,this);
  newb.isDone=true;
  //newb.current=Point(-1,-1);
  return newb;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point)
{
  nextup_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  if (nextup_.empty())
  {
    //this->isDone=true;
  return Point(0, 0);
}
  Point current=nextup_.front();

  nextup_.pop();
  return current;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const
{
  if (nextup_.empty())return Point(-1, -1);
    Point current=nextup_.front();
    return current;
  //return Point(0, 0);
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  if (nextup_.empty())return true;
  else return false;
}
