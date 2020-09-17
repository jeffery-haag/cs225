/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include <string>



class StickerSheet
{
public:
  StickerSheet(const Image & picture,unsigned max);

  ~StickerSheet();
  StickerSheet(const StickerSheet & other);
  const StickerSheet & operator= (const StickerSheet & other);

  int addSticker(Image & sticker,unsigned x, unsigned y);
  void changeMaxStickers(unsigned max);
  Image * getSticker(unsigned index);
  void removeSticker(unsigned index);
  Image render()const;
  bool translate(unsigned index, unsigned x, unsigned y);

  int maxSticks_;
  int counter_;

  Image basePic;
  Image* stickerArray;
  int** xyArr;


};
