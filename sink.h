/*
 * sink.h
 *
 *  Created on: May 14, 2014
 *      Author: Slammy
 */

#ifndef SINK_H_
#define SINK_H_
#include "image.h"

class Image;
class Sink
{
protected:
	Image *input1;
	Image *input2;
	int NumInputs;

public:

	
	virtual void SetInput(Image *img){input1 = img;}
	virtual void SetInput2(Image *img){input2 = img;}	
	virtual const char *SinkName(void) = 0;
	int GetNumInputs(){return NumInputs;}
	
	Sink(void){input1 = NULL; input2 = NULL;}
};



#endif /* SINK_H_ */
