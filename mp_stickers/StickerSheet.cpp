

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
using cs225::HSLAPixel;
using cs225::PNG;
using ::Image;


int maxSticks_;
int counter_;
Image basePic;
Image* stickerArray;
int ** xyArr;

StickerSheet::StickerSheet(const Image & picture,unsigned max):
  maxSticks_(max),
  counter_(0),
  basePic(picture)

  {
  stickerArray=new Image[max];
  xyArr=new int*[maxSticks_];
  for (int i=0;i<(int)max;i++)
  {
    xyArr[i]=new int[2];
  }
}

StickerSheet::~StickerSheet()
{
  for (int i=0;i<this->maxSticks_;i++) delete[] this->xyArr[i];
  delete[] this->xyArr;

  delete[] this->stickerArray;
  //delete this->basePic;
}
StickerSheet::StickerSheet(const StickerSheet & other):
maxSticks_(other.maxSticks_),
counter_(other.counter_),
basePic(other.basePic)
{
  //StickerSheet* copy=new StickerSheet((other.basePic),other.maxSticks_);
  //copy->counter_=other.counter_;

  //maxSticks_=other->maxSticks_;
  //stickerArray=new Image[other->stickerArray.length()];

  stickerArray=new Image[maxSticks_];
  xyArr=new int*[maxSticks_];
  for (int i=0;i<maxSticks_;i++)
  {
    xyArr[i]=new int[2];
  }

  for (int i=0;i<counter_;i++)
  {
    stickerArray[i]=other.stickerArray[i];
    xyArr[i][0]=other.xyArr[i][0];
    xyArr[i][1]=other.xyArr[i][1];
  }


  //Image *basePic=new Image(other->basePic);
}

const StickerSheet & StickerSheet::operator= (const StickerSheet & other)
{
  this->basePic=other.basePic;
  this->maxSticks_=other.maxSticks_;
  this->counter_=other.counter_;
  delete[] this->stickerArray;
  delete[] this->xyArr;
  this->stickerArray=new Image[this->maxSticks_];
  for (int i=0;i<this->counter_;i++)
  {
    this->stickerArray[i]=other.stickerArray[i];
  }
  this->xyArr=new int*[this->maxSticks_];
  for (int i=0;i<(int)maxSticks_;i++)
  {
    xyArr[i]=new int[2];
  }
  for (int i=0;i<this->counter_;i++)
  {
    this->xyArr[i][0]=other.xyArr[i][0];
    this->xyArr[i][1]=other.xyArr[i][1];
  }

return *this;

}
int StickerSheet::addSticker(Image & sticker,unsigned x, unsigned y)
{

  if (counter_>=maxSticks_)return -1;

  this->xyArr[counter_][0]=(int)x;
  this->xyArr[counter_][1]=(int)y;
  this->stickerArray[counter_]=sticker;
  counter_++;

  return counter_-1;

}

void StickerSheet::changeMaxStickers(unsigned max) ///////not remotely done
{
  //int dum=maxSticks_;
  if ((int)max<counter_)counter_=max;
  int** dummyxyArr=new int*[counter_];
  for (int i=0;i<counter_;i++)
  {
    dummyxyArr[i]=new int[2];
  }
  Image* dummyStickerArray=new Image[counter_];

  for (int i=0;i<counter_;i++)
  {
    dummyxyArr[i][0]=xyArr[i][0];
    dummyxyArr[i][1]=xyArr[i][1];
    dummyStickerArray[i]=stickerArray[i];

  }
  for (int i=0;i<maxSticks_;i++) delete[] xyArr[i];
  delete[] xyArr;
  delete[] stickerArray;



  xyArr=new int*[max];
  for (int i=0;i<(int)max;i++)
  {
    xyArr[i]=new int[2];
  }
  stickerArray=new Image[max];


//  int diff=0;
  for (int i=0;i<counter_;i++)
  {
    stickerArray[i]=dummyStickerArray[i];
    xyArr[i][0]=dummyxyArr[i][0];
    xyArr[i][1]=dummyxyArr[i][1];
  }

  maxSticks_=max;


  for (int i=0;i<(int)counter_;i++) delete[] dummyxyArr[i];
  delete[] dummyxyArr;
  delete[] dummyStickerArray;

}


Image * StickerSheet::getSticker(unsigned index)
{
  if (this->counter_<((int)index)+1)return NULL;
  else if (index<0)return NULL;
  else if (this->xyArr[index][0]==-1)return NULL;
  return &(this->stickerArray[index]);
}

Image StickerSheet::render()const
{

  int width=this->basePic.width();
  int height=this->basePic.height();
  //std::cout <<height<<std::endl;
  for (int i=0;i<this->counter_;i++)
  {
    if ((int)this->stickerArray[i].width()+this->xyArr[i][0]>width)width=(int)this->stickerArray[i].width()+this->xyArr[i][0];
    if ((int)this->stickerArray[i].height()+this->xyArr[i][1]>height)height=(int)(this->stickerArray[i].height())+this->xyArr[i][1];
  }
  Image newb(basePic);
  newb.resize(width, height);


for (int i=0;i<counter_;i++)
{
  for (unsigned x = 0; x < this->stickerArray[i].width(); x++) {
		for (unsigned y = 0; y < this->stickerArray[i].height(); y++)
		{

      			HSLAPixel & pixel = this->stickerArray[i].getPixel(x, y);
            if (pixel.a!=0)newb.getPixel(x+this->xyArr[i][0],y+this->xyArr[i][1])=pixel;

		}
  }
}
return newb;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y)
{
  if (this->counter_<(int)index+1)return false;  ///maybe wrong
  else if (index<0)return false;

  this->xyArr[index][0]=x;
  this->xyArr[index][1]=y;
  return true;
}



void StickerSheet::removeSticker(unsigned index)
{

  int dummy=index;
  //stickerArray[index]=;
  xyArr[index][0]=-1;
  xyArr[index][1]=-1;




  if ((int)index<counter_-1)
  {
    for (int i=index;i<counter_-1;i++)
    {
      stickerArray[i]=stickerArray[i+1];
      xyArr[i][0]=xyArr[i+1][0];
      xyArr[i][1]=xyArr[i+1][1];
    }
  }

this->counter_--;

}










//keep page down
