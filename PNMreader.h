/*
 * PNMreader.h
 *
 *  Created on: May 14, 2014
 *      Author: Slammy
 */

#ifndef PNMREADER_H_
#define PNMREADER_H_
#include "source.h"
#include "logging.h"

class PNMreader : public Source
{
protected:
	char *filename;
	void Execute();

public:
	PNMreader(char *f);
	void  Update();
	const char *SourceName(){return "PNMreader";}
};


#endif /* PNMREADER_H_ */
