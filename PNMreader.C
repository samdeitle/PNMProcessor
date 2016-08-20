/*
 * PNMreader.C
 *
 *  Created on: May 14, 2014
 *      Author: Slammy
 */
#include <PNMreader.h>

PNMreader::PNMreader(char *f)
{filename = f;}

void PNMreader::Update()
{
	char msg[128];
	
	sprintf(msg, "%s---about to execute\n", SourceName());
	Logger::LogEvent(msg);

	try{Execute();}
	catch(DataFlowException &e)
	{
		const char *msg = e.what();
		Logger::LogEvent(msg);
		throw e;
	}

	updated = true;
	sprintf(msg, "%s---execute success\n", SourceName());
	Logger::LogEvent(msg);
}

void PNMreader::Execute()
{


	FILE *f = fopen(filename, "rb");
	    char magicNum[128];
	    int  width, height, maxval;

	    if (f == NULL)
	    {
	    	char msg[128];
	        sprintf(msg, "Unable to open file %s\n", filename);
	        throw DataFlowException(SourceName(), msg);
	    }

	    fscanf(f, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);

	 /* file position is at first byte of image data. */
	    int i,j;
	    image.SetSize(height, width);
	    unsigned char data[3];
	    for (i = 0; i < height;i++)
	    {

	    	for (j = 0; j < width;j++)
	    	{
	    		fread(data, 1, 3, f);
		    	Pixel tmp;
		    	tmp.r = data[0];
		    	tmp.g = data[1];
		    	tmp.b = data[2];
		    	image.pic[i][j] = tmp;
//		    	if (i==j){printf("At i,j:(%d, %d)---r: %d, g: %d, b: %d \n", i, j, image.pic[i][i].r,image.pic[i][i].g,image.pic[i][i].b);}
	    	}
	    }

	    fclose(f);

}
