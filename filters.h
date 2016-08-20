/*
 * filters.h
 *
 *  Created on: May 14, 2014
 *      Author: Slammy
 */

#ifndef FILTERS_H_
#define FILTERS_H_
#include "source.h"
#include "sink.h"
#include "logging.h"
#include <string.h>

class Color : public Source
{public:

	void Update();
	void Execute();
	const char *SourceName(){return "Constant Color";};
	Color(int w, int h, unsigned char r, unsigned char g, unsigned char b){height = h; width = w; red = r; green = g; blue = b; image.SetSize(h, w);}

protected:
	int height, width; unsigned char red, blue, green;
};

class CheckSum : public Sink
{public:
	void OutputCheckSum(char *f);

	const char *SinkName(){return "CheckSum";};
	CheckSum(){NumInputs = 1;};

};

class Filter : public Source, public Sink
{public:

	virtual const char *FilterName(void) = 0;
	void 		    Update();
	const char 	   *SourceName();
	const char 	   *SinkName();
};

class Shrinker : public Filter
{public:
	void Execute();


	const char *FilterName(){return "Shrinker";}
	Shrinker(void){NumInputs = 1;}
};

class LRConcat : public Filter
{public:
	void Execute();

	const char *FilterName(){return "LRConcat";}
	LRConcat(void){NumInputs = 2;}
};

class TBConcat : public Filter
{public:
	void Execute();

	const char *FilterName(){return "TBConcat";}
	TBConcat(void){NumInputs = 2;}
};

class Blender : public Filter
{
protected:
	float factor;
public:
	void SetFactor(float f);
	void Execute();

	const char *FilterName(){return "Blender";}
	Blender(void){NumInputs = 2;}
};


class Transpose : public Filter
{
public:
	void Execute();

	const char *FilterName(){return "Transpose";};
	Transpose(void){NumInputs = 1;}
};

class Invert : public Filter
{
public:
	void Execute();

	const char *FilterName(){return "Invert";};
	Invert(void){NumInputs = 1;}
};

class Crop : public Filter
{
  public:
                   Crop()  { Istart = Istop = Jstart = Jstop = -1; NumInputs = 1;};
    virtual const char *FilterName() { return "Crop"; };
    virtual void   Execute();
    void           SetRegion(int Jstart_, int Jstop_, int Istart_, int Istop_)
                      {
                        Istart = Istart_;
                        Istop  = Istop_;
                        Jstart = Jstart_;
                        Jstop  = Jstop_;
                      }
  private:
    int Istart, Istop, Jstart, Jstop;
};



#endif /* FILTERS_H_ */
