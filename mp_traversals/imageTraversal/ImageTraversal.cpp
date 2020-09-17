#include <cmath>
#include <iterator>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>


#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 ImageTraversal::Iterator::Iterator();
 {
   double done=0;
 }
 */

ImageTraversal::Iterator::Iterator(PNG & Image1, Point & begin1, double tol1,ImageTraversal* tra)
{

  tol=tol1;
  begin=begin1;
  //std::queue<Point> nextup=nextup_;
  image=PNG(Image1);
  current=begin;
  //std::vector<Point> dead;
  thisIt=tra;
  isDone=false;
  for (unsigned i=0;i<(image.width()*image.height());i++)
  {
    dead.push_back(true);
  }

}
ImageTraversal::Iterator::Iterator(int a,PNG & Image1, Point & begin1, double tol1,ImageTraversal* tra)
{
  tol=tol1;
  begin=begin1;
  //std::stack<Point> nextup=nextup_;
  image=Image1;
  current=begin;
  //std::vector<Point> dead;
  thisIt=tra;
  isDone=false;
  for (unsigned i=0;i<(image.width()*image.height());i++)
  {
    dead.push_back(true);
  }
}

bool ImageTraversal::Iterator::isSafe(Point point)
{
  if (point.x>=image.width())return false;
  if (point.y>=image.height())return false;
  if (point.x<0)return false;
  if (point.y<0)return false;
  if (calculateDelta(image.getPixel(point.x,point.y),
  image.getPixel(begin.x,begin.y)) > tol)return false;//meets tolertance

    return (dead[point.y*image.width()+point.x]);

//  return true;

}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */

ImageTraversal::Iterator & ImageTraversal::Iterator::operator++()
{
  //Point* newOne=new Point();
  //current=this->ourGuy->nextup.pop()//current becomes next pixels



    newOne=Point(current.x+1,current.y);//right
    if (this->isSafe(newOne))
    {
      thisIt->add(newOne);
      //dead.push_back(newOne);
    }
    newOne=Point(current.x,current.y+1);//below
    if (this->isSafe(newOne))
    {
      thisIt->add(newOne);
      //dead.push_back(newOne);
    }
    newOne=Point(current.x-1,current.y);//left
    if (this->isSafe(newOne))
    {
      thisIt->add(newOne);
      //dead.push_back(newOne);
    }
    newOne=Point(current.x,current.y-1);//above
    if (this->isSafe(newOne))
    {
      thisIt->add(newOne);
      //dead.push_back(newOne);
    }

  //  dead.push_back(current);
  dead[current.y*image.width()+current.x]=false;

    if (thisIt->empty())
    {
      isDone=true;
      //current=Point(-1,-1);
      return *this;
    }
    Point dummy=current;

    while(current==dummy)
    {
    if (this->isSafe(thisIt->peek()))
    {
      //dead.push_back(current);
      current=thisIt->pop();
    }
    else thisIt->pop();

    if (thisIt->empty())
    {
      isDone=true;
      //current=Point(-1,-1);
      return *this;
    }

    }
    if (thisIt->empty())isDone=true;

  return *this;

}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*()
{
  return this->current;
  //return Point(0, 0);
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other)
{
  //Point faker=this->current;
  //if (faker.x!=other.current.x)return true;
  //if (faker.y!=other.current.y)return true;
  //if (faker.x==-1 && other.current.x==-1)return false;
  return (other.isDone !=isDone);
  return true;
}
