/*
 * PNMwriter.C
 *
 *  Created on: May 14, 2014
 *      Author: Slammy
 */
#include <PNMwriter.h>
#include <string.h>

void PNMwriter::Write(char *filename)
{
	FILE *f       = fopen(filename, "wb");

	int height    = input1->height;
	int width     = input1->width;

	char header[17];
	sprintf(header, "P6\n%d %d\n255\n", width, height);

	fwrite(header, strlen(header), 1, f);
	int i;
	for (i = 0; i < height; i++){fwrite(input1->pic[i], width*3, 1, f);}

	fclose(f);
}

