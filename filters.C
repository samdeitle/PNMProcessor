/*
 * filters.C
 *
 *  Created on: May 14, 2014
 *      Author: Slammy
 */
#include <filters.h>
#include <stdio.h>

void Color::Update()
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

void Color::Execute()
{
    char msg[128];

    if (height <= 0 || width <= 0)
    {
        sprintf(msg, "Invalid size: height = %d, width = %d", height, width);
        throw DataFlowException(SourceName(), msg);
    }

    if (red > 255 || red < 0 || green > 255 || green < 0 || blue > 255 || blue < 0)
    {
        sprintf(msg, "Invalid color input (must be in range 0-255): red = %d, green = %d, blue = %d", red, green, blue);
        throw DataFlowException(SourceName(), msg);
    }

    const int h = height;
    const int w = width;

    Pixel **buffer = image.pic;
    Pixel tmp;

    tmp.r = red;
    tmp.g = green;
    tmp.b = blue;

    for (int i = 0; i < h; i++)
    {for (int j = 0; j < w; j++)
    {
        buffer[i][j] = tmp;
    }
    }

}

void CheckSum::OutputCheckSum(char *f)
{
    FILE *f_out = fopen(f, "w");

    unsigned char R = 0;
    unsigned char G = 0;
    unsigned char B = 0;

    int h = input1->height;
    int w = input1->width;

    Pixel **buffer = input1->pic;

    for (int i = 0; i < h; i++)
    {for (int j = 0; j < w; j++)
    {
        R += buffer[i][j].r;
        G += buffer[i][j].g;
        B += buffer[i][j].b;
    }
    }
    char msg[128];
    sprintf(msg, "CHECKSUM: %d, %d, %d\n", R, G, B);
    fwrite(msg, 1, strlen(msg), f_out);

    fclose(f_out);
}

void Filter::Update()
{
    char msg[128];
    
    if(input1 == NULL)
    {
        sprintf(msg, "Throwing Exception: Input1 not set\n");
        throw DataFlowException(FilterName(), msg);
    }

    if(!(input1->f->updated)){
        sprintf(msg, "%s---about to Update input1\n", FilterName());
        Logger::LogEvent(msg);

        try{
            input1->Image::Update();

            sprintf(msg, "%s---Update input1 success\n", FilterName());
            Logger::LogEvent(msg);
        }

        catch(DataFlowException &e)
        {
            char log[128];
            sprintf(log, "%s---Update input1 failure\n", FilterName());
            Logger::LogEvent(log);

            throw e;
        }
    }

    if(GetNumInputs() == 2){

        if(input2 == NULL)
        {
            sprintf(msg, "Throwing Exception: Input2 not set\n");
            throw DataFlowException(FilterName(), msg);
        }

        if (!(input2->f->updated)){
            sprintf(msg, "%s---about to Update input2\n", FilterName());
            Logger::LogEvent(msg);

            try{
                input2->Image::Update();

                sprintf(msg, "%s---Update input2 success\n", FilterName());
                Logger::LogEvent(msg);
            }
            catch(DataFlowException &e)
            {
                char log[128];
                sprintf(log, "%s---Update input2 failure\n", FilterName());
                Logger::LogEvent(log);

                throw e;
            }

        }
    }


    if (!updated){

        sprintf(msg, "%s---about to execute\n", FilterName());
        Logger::LogEvent(msg);

        updated = true;

        try{Execute();}
        catch (DataFlowException &e)
        {
            const char *msg = e.what();
            Logger::LogEvent(msg);
            throw e;
        }

        sprintf(msg,"%s---done executing\n", FilterName());
        Logger::LogEvent(msg);
    }
}
const char *Filter::SourceName()
{
    return FilterName();}


const char *Filter::SinkName()
{
    return FilterName();
}


void Shrinker::Execute()
{
    int h = input1->height;
    int w = input1->width;
    int new_h, new_w;

    if (h % 2 == 0){new_h = (h/2);}
    else{new_h = (h-1)/2;}

    if (w % 2 == 0){new_w = (w/2);}
    else{new_w = (w-1)/2;}

    image.SetSize(new_h, new_w);
    for (int i = 0; i < new_h; i++)
    {for (int j = 0; j < new_w; j++)
        {image.pic[i][j] = input1->pic[i*2][j*2];}
    }
}

void LRConcat::Execute()
{
        int h  = input1->height;
        int h1 = input2->height;

        if (h != h1)
        {
            char log[128];
            sprintf(log, "Throwing Exception: Height mismatch: L-height = %d, R-height = %d\n", h, h1);
            throw DataFlowException(FilterName(), log);
        }

        int w1 = input1->width;
        int w2 = input2->width;
        int new_w = w1 + w2;

        image.SetSize(h, new_w);
        for (int i = 0; i < h; i++)
        {for (int j = 0; j < w1; j++)
            {image.pic[i][j]      = input1->pic[i][j];}
         for (int k = 0; k < w2; k++)
            {image.pic[i][w1 + k] = input2->pic[i][k];}

        }
}

void TBConcat::Execute()
{
    int w  = input1->width;
        int w1 = input2->width;

        if (w != w1)
        {
            char log[128];
            sprintf(log, "Throwing Exception: Width mismatch: Top width = %d, Bottom width = %d\n", w, w1);
            throw DataFlowException(FilterName(), log);
        }

        int h1 = input1->height;
        int h2 = input2->height;
        int new_h = h1 + h2;

        image.SetSize(new_h, w);
        int i, j;

        for (i = 0; i < h1; i++)
        {for (j = 0; j < w; j++)
            {image.pic[i][j] = input1->pic[i][j];}
        }

        for (i = 0; i < h2; i++)
        {for (j = 0; j < w; j++)
            {image.pic[i + h1][j] = input2->pic[i][j];}
        }
}

void Blender::SetFactor(float f)
{factor = f;}

void Blender::Execute()
{
    if(factor > 1){
        char msg[128];
        sprintf(msg, "Throwing Exception: blend factor > 1\n");
        throw DataFlowException(FilterName(), msg);
    }

    int h = input1->height;
    int h1 = input2->height;

    if (h != h1)
    {
        char log[128];
        sprintf(log, "Throwing Exception: Height mismatch: L-height = %d, R-height = %d\n", h, h1);
        throw DataFlowException(FilterName(), log);
    }

    int w  = input1->width;
    int w1 = input2->width;

    if (w != w1)
    {
        char log[128];
        sprintf(log, "Throwing Exception: Width mismatch: Top width = %d, Bottom width = %d\n", w, w1);
        throw DataFlowException(FilterName(), log);
    }

    float V1 = factor;
    float V2 = 1 - factor;
    image.SetSize(h, w);

    for (int i = 0; i < h; i++)
    {for (int j = 0; j < w; j++)
    {
        Pixel pix1    = input1->pic[i][j];
        Pixel pix2    = input2->pic[i][j];
        Pixel new_pix;

        float r1 = float (pix1.r);
        float r2 = float (pix2.r);
        float new_r = (V1*r1) + (V2*r2);

        float g1 = pix1.g;
        float g2 = pix2.g;
        float new_g = (V1*g1) + (V2*g2);

        float b1 = pix1.b;
        float b2 = pix2.b;
        float new_b = (V1*b1) + (V2*b2);

        new_pix.r = new_r;
        new_pix.g = new_g;
        new_pix.b = new_b;

        image.pic[i][j] = new_pix;
    }
    }
}

void Transpose::Execute()
{
    int h = input1->width;
    int w = input1->height;

    image.SetSize(h, w);
    Pixel **buffer = image.pic;
    Pixel **buffer1 = input1->pic;
    for (int i = 0; i < h; i++)
    {for (int j = 0; j < w; j++)
    {
        buffer[i][j] = buffer1[j][i];
    }
    }
}

void Invert::Execute()
{
    int h = input1->height;
    int w = input1->width;

    image.SetSize(h, w);
    Pixel **buffer = image.pic;
    Pixel **buffer1 = input1->pic;
    
    unsigned char new_r;
    unsigned char new_g;
    unsigned char new_b;

    for (int i = 0; i < h; i++)
        {for (int j = 0; j < w; j++)
        {
            Pixel pix    = buffer1[i][j];

            Pixel new_pix;

            new_r = 255 - pix.r;

            new_g = 255 - pix.g;

            new_b = 255 - pix.b;

            new_pix.r = new_r;
            new_pix.g = new_g;
            new_pix.b = new_b;

            buffer[i][j] = new_pix;
        }
        }
}

void
Crop::Execute(void)
{

    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istart < 0 || Istop > input1->height)
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Jstart < 0 || Jstop > input1->width)
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }

    int width = Jstop-Jstart+1;
    int height  = Istop-Istart+1;
    int inputWidth = input1->width;
    image.SetSize(height, width);
    Pixel **buffer = image.pic;
    Pixel **buffer1 = input1->pic;


    int new_i = 0; int new_j = 0;
    for (int i = Istart ; i <= Istop ; i++){
        new_j = 0;
    for (int j = Jstart ; j <= Jstop ; j++)
        {
//          /*if (new_i == new_j*/fprintf(stderr, "Where's the beef? %d, %d\n", i, j);
            buffer[new_i][new_j] = buffer1[i][j];
            new_j++;
    }
        new_i++;
    }
}
