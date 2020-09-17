#include "../cs225/catch/catch.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../cs225/PNG.h"
#include "../cs225/LUVAPixel.h"
#include "../maptiles.h"
#include "../mosaiccanvas.h"
#include "../cs225/RGB_LUV.h"

using namespace cs225;

LUVAPixel redLUVAPixel() {
  rgbaColor rgb;
  rgb.r = 255; rgb.g = 0; rgb.b = 0; rgb.a = 255;
  luvaColor luv = rgb2luv(rgb);
  return LUVAPixel(luv.l, luv.u, luv.v, luv.a);
}

LUVAPixel greenLUVAPixel() {
  rgbaColor rgb;
  rgb.r = 0; rgb.g = 255; rgb.b = 0; rgb.a = 255;
  luvaColor luv = rgb2luv(rgb);
  return LUVAPixel(luv.l, luv.u, luv.v, luv.a);
}

LUVAPixel blueLUVAPixel() {
  rgbaColor rgb;
  rgb.r = 0; rgb.g = 0; rgb.b = 255; rgb.a = 255;
  luvaColor luv = rgb2luv(rgb);
  return LUVAPixel(luv.l, luv.u, luv.v, luv.a);
}

TEST_CASE("Creates a basic MosaicCanvas (gridtest)", "[weight=5][part=2]") {
  // Read `tests/gridtest.png` from disk


  PNG sourcePNG;
  sourcePNG.readFromFile("iamges/base.png");
  SourceImage source(sourcePNG, 8);

  // Create a list of images to choose from to make our mosaic.  As a basic
  // test, we'll use images of one pixel colored either red, green, or blue.
  vector<TileImage> tileList;



  PNG a;
  PNG b;
  PNG c;
  PNG d;
  PNG e;
  PNG f;
  PNG g;
  PNG h;
  PNG i;

  a.readFromFile("iamges/a.png");
  b.readFromFile("iamges/c.png");
  c.readFromFile("iamges/d.png");
  d.readFromFile("iamges/e.png");
  e.readFromFile("iamges/b.png");
  f.readFromFile("iamges/f.png");
  g.readFromFile("iamges/g.png");
  h.readFromFile("iamges/h.png");
  i.readFromFile("iamges/i.png");


  tileList.push_back(TileImage(a));
  tileList.push_back(TileImage(b));
  tileList.push_back(TileImage(c));
  tileList.push_back(TileImage(d));
  tileList.push_back(TileImage(e));
  tileList.push_back(TileImage(f));
  tileList.push_back(TileImage(g));
  tileList.push_back(TileImage(h));
  tileList.push_back(TileImage(i));



  // Draw the mosaic!
  MosaicCanvas* canvas = mapTiles(source, tileList);
  REQUIRE( canvas != NULL );
//std::cout<<"here"<<std::endl;
  PNG actual = canvas->drawMosaic(100);
  PNG expected;  expected.readFromFile("tests/gridtest-expected.png");
//std::cout<<"here"<<std::endl;
  // Save and check for correctness
  actual.writeToFile("mymosaic.png");
  INFO("Saved `actual` as gridtest-actual.png.");
//std::cout<<"here"<<std::endl;
  REQUIRE( actual == expected );
  delete canvas; canvas = NULL;
}
