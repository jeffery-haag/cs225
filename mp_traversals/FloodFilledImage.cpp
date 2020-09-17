#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  image = new PNG(png);
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  ImageTraversal* trav = &traversal;
  travv.push_back(trav);
  ColorPicker* color = &colorPicker;
  colPick.push_back(color);
}


Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;


  animation.addFrame(*image);

  for (unsigned i = 0; i < travv.size(); i++)
  {
    ImageTraversal::Iterator beg = travv[i]->begin();

    ImageTraversal::Iterator ender = travv[i]->end();
    unsigned a = 0;
    while (beg != ender )
    {
      if (a == frameInterval)
      {
        animation.addFrame(*image);
        a = 0;
      }
      a++;
      HSLAPixel& original = image->getPixel((*beg).x, (*beg).y);

      HSLAPixel newone = colPick[i]->getColor((*beg).x, (*beg).y);
      original.h = newone.h;

      original.s = newone.s;

      original.l = newone.l;

      original.a = newone.a;
      ++beg;
    }
    animation.addFrame(*image);
  }

  return animation;
}
