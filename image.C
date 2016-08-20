/*
 * image.C
 *
 *  Created on: May 7, 2014
 *      Author: Slammy
 */
#include "image.h"
#include "filters.h"


Image::Image()
{
	height = 0; width = 0;
	f = NULL; pic = NULL;
}

Image::Image(int h, int w, Pixel **p)
{
	height = h; width = w;
	f = NULL; pic = p;
}

Image::Image(int h, int w)
{
	height = h; width = w;
	pic = new Pixel*[height];
	for (int i = 0; i < height; i++)
		{pic[i] = new Pixel[width];}
	f = NULL;
}

Image::Image(Image &i)
{
	height = i.height; width = i.width;
	f = i.f; pic = i.pic;
}

void Image::SetSize(int h, int w)
{
	height = h; width = w;
	pic = new Pixel*[height];
	for (int i = 0; i < height; i++)
		{pic[i] = new Pixel[width];}
}

void Image::Update() const
{
	try{f->Update();}
	catch(DataFlowException &e){throw e;}
}


Image::~Image()
{
	
}
