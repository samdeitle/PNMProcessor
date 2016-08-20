/*
 * source.h
 *
 *  Created on: May 14, 2014
 *      Author: Slammy
 */

#ifndef SOURCE_H_
#define SOURCE_H_
#include "image.h"
#include <stdio.h>
#include "logging.h"

class Image;
class Source
{

protected:
	Image image;
	virtual void Execute(void)     = 0;
	
public:
	bool updated;
	virtual void Update(void)		   = 0;
	Image* GetOutput(){return &image;}
	virtual const char *SourceName(void) = 0;
	Source(void){image.f = this; updated = false;}
};





#endif /* SOURCE_H_ */
