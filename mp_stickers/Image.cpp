

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
//#include <cmath>
#include <iostream>
#include <cmath>
#include <cstdlib>

using cs225::HSLAPixel;
using cs225::PNG;



void Image::lighten(){
for (unsigned int x=0;x<this->width();x++){
  for (unsigned int y=0;y<this->height();y++){
    if ((this->getPixel(x,y)).l<0.9)(this->getPixel(x,y)).l+=.1;
    else (this->getPixel(x,y)).l=1;
  }
}
}

void Image::lighten(double amount){
for (unsigned int x=0;x<this->width();x++){
  for (unsigned int y=0;y<this->height();y++){
    if ((this->getPixel(x,y)).l<(1-amount))(this->getPixel(x,y)).l+=amount;
    else (this->getPixel(x,y)).l=1;
  }
}
}

void Image::darken(){
for (unsigned int x=0;x<this->width();x++){
  for (unsigned int y=0;y<this->height();y++){
    if ((this->getPixel(x,y)).l>(0.1))(this->getPixel(x,y)).l-=0.1;
    else (this->getPixel(x,y)).l=0;
  }
}
}

void Image::darken(double amount){
for (unsigned int x=0;x<this->width();x++){
  for (unsigned int y=0;y<this->height();y++){
    if ((this->getPixel(x,y)).l>(amount))(this->getPixel(x,y)).l-=amount;
    else (this->getPixel(x,y)).l=0;
  }
}
}

void Image::saturate(){
for (unsigned int x=0;x<this->width();x++){
  for (unsigned int y=0;y<this->height();y++){
    if ((this->getPixel(x,y)).s<(.9))(this->getPixel(x,y)).s+=0.1;
    else (this->getPixel(x,y)).s=1;
  }
}
}

void Image::saturate(double amount){
for (unsigned int x=0;x<this->width();x++){
  for (unsigned int y=0;y<this->height();y++){
    if ((this->getPixel(x,y)).s<(1-amount))(this->getPixel(x,y)).s+=amount;
    else (this->getPixel(x,y)).s=1;
  }
}
}

void Image::desaturate(){
for (unsigned int x=0;x<this->width();x++){
  for (unsigned int y=0;y<this->height();y++){
    if ((this->getPixel(x,y)).s>(.1))(this->getPixel(x,y)).s-=.1;
    else (this->getPixel(x,y)).s=0;
  }
}
}

void Image::desaturate(double amount){
for (unsigned int x=0;x<this->width();x++){
  for (unsigned int y=0;y<this->height();y++){
    if ((this->getPixel(x,y)).s>(amount))(this->getPixel(x,y)).s-=amount;
    else (this->getPixel(x,y)).s=0;
  }
}
}

void Image::grayscale(){
for (unsigned int x=0;x<this->width();x++){
  for (unsigned int y=0;y<this->height();y++){
    (this->getPixel(x,y)).s=0;
  }
}
}

void Image::rotateColor(double degrees){
for (unsigned int x=0;x<this->width();x++){
  for (unsigned int y=0;y<this->height();y++){
    if ((this->getPixel(x,y)).h+degrees<360  &&  (this->getPixel(x,y).h+degrees)>0)
    (this->getPixel(x,y)).h+=degrees;
    else if (this->getPixel(x,y).h+degrees<0)this->getPixel(x,y).h=(360-abs(this->getPixel(x,y).h+degrees));
    else(this->getPixel(x,y)).h=(degrees+(this->getPixel(x,y)).h-360);
  }
}
}

void Image::illinify( ){
for (unsigned int x=0;x<this->width();x++){
  for (unsigned int y=0;y<this->height();y++){
    HSLAPixel & pixel = this->getPixel(x, y);
			unsigned int a = pixel.h;

			if ( ( abs(216.0-a) < abs(11.0-a)  ||  (a+360-216) < abs(11.0-a)  )  &&
			(   abs(216.0-a) < (360+11.0-a)  ||  (a+360-216) < (360+11.0-a)   )  )pixel.h=216;
			else pixel.h=11;
  }
}
}

void Image::scale(double factor){
  double rat=(1.0/factor);

  PNG *ogImage=new PNG(*this);
  this->resize(factor*((double)this->width()),factor*((double)this->height()));
  for (unsigned x=0;x<this->width();x++){
    for (unsigned y=0;y<this->height();y++){
      this->getPixel(x,y)=ogImage->getPixel(floor(x*(rat)),floor(y*(rat)));
    }

  }
  delete ogImage;
}

void Image::scale(unsigned w, unsigned h)
  {
    double wRat=(double)w/this->width();
    double hRat=(double)h/this->height();

    if (wRat>hRat)this->scale(hRat);
    else this->scale(wRat);
/*


    PNG *ogImage=new PNG(*this);
    this->resize((double)w,(double)h);
    for (unsigned x=0;x<w;x++){
      for (unsigned y=0;y<h;y++){
        this->getPixel(x,y)=
        ogImage->getPixel(floor(x*(1/wRat)),floor(y*(1/hRat)));
      }

    }
    delete ogImage;

*/
}
