#include "Image.h"
#include "StickerSheet.h"

using namespace cs225;
int main() {

  Image background;
  background.readFromFile("alma.png");
  background.illinify();

  Image i;
  i.readFromFile("i.png");
  Image ismall(i);
  ismall.scale(.3);
  Image igray(i);
  igray.grayscale();


  StickerSheet stick(background, 4);
  stick.addSticker(i, 69, 69);
  stick.addSticker(ismall, 0, 0);
  stick.addSticker(igray, 600, 12);

  Image out=stick.render();
  out.writeToFile("myImage.png");





  return 0;
}
