#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance)
{
  tol=tolerance;
  begins=start;
  //nextup_=new std::stack<Point&>
  image=PNG(png);
  failsafe=false;
  this->add(begins);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(1,this->image,this->begins,this->tol,this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end()
 {
  /** @todo [Part 1] */
//  return ImageTraversal::Iterator();
  ImageTraversal::Iterator newb=ImageTraversal::Iterator(1,this->image,this->begins,this->tol,this);
  newb.isDone=true;
  //newb.current=Point(-1,-1);
  return newb;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point)
{
  nextup_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop()
{
  if (nextup_.empty())
  return Point(-1, -1);
  Point current=nextup_.top();

  nextup_.pop();
  return current;
  //return Point(0, 0);
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const
{
  if (nextup_.empty())return Point(-1, -1);
    Point current=nextup_.top();
    return current;
  //return Point(0, 0);
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const
{
  if (nextup_.empty())return true;
  else return false;
}
