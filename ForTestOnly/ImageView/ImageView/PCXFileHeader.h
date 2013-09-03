#pragma once
#ifndef _IMAGEVIEW_PCXFILEHEADER_H
#define _IMAGEVIEW_PCXFILEHEADER_H
typedef struct  
{
    char manufacturer;
    char version;
    char encoding;
    char bitsPerPixel;
    short xmin, ymin;
    short xmax, ymax;
    char palette[48];
    char colorPlanes;
    short bytesPerLine;
    short paletteType;
    char filter[58];
}PCXFILEHEADER;
#endif