#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
	

void rotate(std::string inputFile, std::string outputFile) 
{
	cs225::PNG png;
	png.readFromFile(inputFile);
	int width=png.width();
	int height=png.height();
	//cs225::HSLAPixel dummy;
	for (int y=0;y<height/2;y++){
	   for (int x=0;x<width;x++)
	   {
		cs225::HSLAPixel dummy = png.getPixel(x,y); 
		png.getPixel(x,y)=png.getPixel(x,height-1-y);
		png.getPixel(x,height-1-y)=dummy;

	   }
	}
	for (int y=0;y<height;y++){
	   for (int x=0;x<width/2;x++)
	   {
		cs225::HSLAPixel dummy = png.getPixel(x,y); 
		png.getPixel(x,y)=png.getPixel(width-1-x,y);
		png.getPixel(width-1-x,y)=dummy;

	   }
	}
	png.writeToFile(outputFile);
	
}

cs225::PNG myArt(unsigned int width, unsigned int height) 
{
	cs225::PNG png(width, height);
 	for (unsigned int x=0;x<width/3;x++){
	   for (unsigned int y=0;y<(height/4+10);y++){
		cs225::HSLAPixel & dummy = png.getPixel(x,y); 
		dummy.h=240;	//blue
		dummy.l=.5;
		dummy.s=1;
	   }
	}
	int bars=0;
	for (unsigned int y=0;y<height/4;y++){
	   bars++;
	   for (unsigned int x=height/3-1;x<width;x++){
		
		cs225::HSLAPixel & dummy = png.getPixel(x,y); 
		if (bars%32>16)
		{
		dummy.h=240;	
		dummy.l=1;
		dummy.s=1;				//white
		}
		else 
		{
		dummy.h=359;	
		dummy.l=.5;
		dummy.s=1;			//red
		}
	   }
	}
	for (unsigned int y=height/4;y<height/2;y++){
	   bars++;
	   for (unsigned int x=0;x<width;x++){
		
		cs225::HSLAPixel & dummy = png.getPixel(x,y); 
		if (bars%32>16)
		{
		dummy.h=240;	
		dummy.l=1;
		dummy.s=1;				//white
		}
		else 
		{
		dummy.h=359;	
		dummy.l=.5;
		dummy.s=1;			//red
		}
	   }
	}




	for (unsigned int x=0;x<width/3;x++){
	   for (unsigned int y=height/2;y<height;y++){
		cs225::HSLAPixel & dummy = png.getPixel(x,y); 
		dummy.h=98;	//green
		dummy.l=.36;
		dummy.s=1;
	   }
	}
	for (unsigned int x=width/3;x<2*width/3;x++){
	   for (unsigned int y=height/2;y<height;y++){
		cs225::HSLAPixel & dummy = png.getPixel(x,y); 
		dummy.h=240;	//white
		dummy.l=1;
		dummy.s=1;
	   }
	}
	for (unsigned int x=2*width/3;x<width;x++){
	   for (unsigned int y=height/2;y<height;y++){
		cs225::HSLAPixel & dummy = png.getPixel(x,y); 
		dummy.h=359;	//red
		dummy.l=.5;
		dummy.s=1;
	   }
	}
	

	return png;



















}
