/*
 * image.h
 *
 *  Created on: May 7, 2014
 *      Author: Slammy
 */

#ifndef IMAGE_H_
#define IMAGE_H_


#include <stdlib.h>

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Pixel;

class Source;
class Image
{
private:

	Image & operator = (const Image &){;};

public:
	
	Pixel **pic;
	int height; int width;
	Source *f;


	Image(void);
	Image(int h, int w, Pixel **p);
	Image(int h, int w);
	Image(Image &);
	~Image();	


	void SetSize(int h, int w);
	void Update() const;
};

#endif /* IMAGE_H_ */
