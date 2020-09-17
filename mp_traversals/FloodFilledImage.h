/**
 * @file FloodFilledImage.h
 * Definition for a class to do flood fill on an image
 */

 #include "cs225/PNG.h"
 #include <list>
 #include <vector>
 #include <iostream>

 #include "colorPicker/ColorPicker.h"
 #include "imageTraversal/ImageTraversal.h"

 #include "Point.h"
 #include "Animation.h"

 using namespace cs225;

 class FloodFilledImage {
 public:
   FloodFilledImage(const PNG & png);
   void addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker);
   Animation animate(unsigned frameInterval) const;

 private:

   PNG* image;
   vector<ImageTraversal*> travv;
   vector<ColorPicker*> colPick;

 };
