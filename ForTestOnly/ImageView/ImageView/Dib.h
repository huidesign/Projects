#pragma once
#ifndef _IMAGEVIEW_DIB_H
#define _IMAGEVIEW_DIB_H
#include <Windows.h>

class CDib
{
public:
    CDib(void);
    virtual ~CDib(void);
    void Clear();
    int GetWidth() {return m_nWidth;}
    int GetHeight() {return m_nHeight;}
    int GetBitCount() {return m_nBitCount;}
    BOOL IsEmpty() {return !m_lpBits;}
    int Stretch(HDC hDc, int XDest, int YDest, int nDestWidth, int nDestHeight,
                int XSrc, int YSrc, int nSrcWidth, int nSrcHeight, UINT iUsage, DWORD dwRop);
    BOOL LoadFromFile(CFile *pFile);
    BOOL LoadFromFile(LPCTSTR fileName);
    BOOL SaveToFile(CFile *pFile);
    BOOL SaveToFile(LPCTSTR fileName);
    BOOL ImportPCX(char *fileName);
    BOOL ImageCopy();
    BOOL ImagePaste();
    BOOL HorizonFlip();
    BOOL VerticalFlip();
    BOOL RotateLeft();
    BOOL RotateRight();
    BOOL ConvertGrey();
    BOOL ConvertNegative();

private:
    BYTE *m_lpBits;
    BYTE *m_lpPalette;
    int m_nWidth;
    int m_nHeight;
    int m_nBitCount;
    
    BOOL LoadDib(BYTE *lpDib);
    BOOL SaveToDib(BYTE *lpDib);
};

#endif