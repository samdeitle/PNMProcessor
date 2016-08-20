/*
 * PNMwriter.h
 *
 *  Created on: May 14, 2014
 *      Author: Slammy
 */

#ifndef PNMWRITER_H_
#define PNMWRITER_H_
#include <sink.h>
#include <stdio.h>

class PNMwriter : public Sink
{
protected:
	char *filename;

public:
	
	void Write(char *f);
	void Execute();

	const char *SinkName(){return "PNMwriter";}
};



#endif /* PNMWRITER_H_ */
