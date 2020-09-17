/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
  vector<Point<3>> vect;
  vect.resize(theTiles.size());
  map<Point<3>, TileImage*> huh;
  int row=theSource.getRows();
  int cols=theSource.getColumns();
  MosaicCanvas* fin=new MosaicCanvas(row,cols);

  for (unsigned i=0;i<theTiles.size();i++)
  {
    LUVAPixel temp=(theTiles[i]).getAverageColor();
    Point<3> pixelpoo(temp.l,temp.u,temp.v);
    huh[pixelpoo]=&theTiles[i];
    vect.push_back(pixelpoo);
  }
  KDTree<3> tree(vect);

  for (int x=0;x<row;x++)
  {
    for (int y=0;y<cols;y++)
    {
      LUVAPixel temp=theSource.getRegionColor(x,y);
      Point<3> findit(temp.l,temp.u,temp.v);
      Point<3> closest=tree.findNearestNeighbor(findit);
      TileImage* almost=huh[closest];
      fin->setTile(x,y,almost);
    }
  }


  return fin;

    //eturn NULL;
}
