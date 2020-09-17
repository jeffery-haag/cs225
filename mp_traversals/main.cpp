
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  PNG image;
  pic.readFromFile("tests/pacman-solid-dfs.png");
    DFS traverse(image, Point(50,50),.3);
    RainbowColorPicker colors(0.05);
    BFS traverse2(image, Point(0,0),.3);
    FloodFilledImage pic(image);
    pic.addFloodFill(traverse,colors);
      pic.addFloodFill(traverse2,colors);
      
      MyColorPicker colors2(0.05);
      pic.addFloodFill(traverse2,colors2);
 
 Animation animation =image.animate(888);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  


  return 0;
}
