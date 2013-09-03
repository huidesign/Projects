#include "StdAfx.h"
#include "ImageView.h"
#include "Dib.h"
#include "PCXFileHeader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#define BYTE_PER_LINE(w,c) ((((w)*(c)+31)/32)*4)
#define PALETTESIZE(b) (((b)==8)?256:(((b)==4)?16:0))

CDib::CDib(void)
    : m_lpBits(NULL),
      m_lpPalette(NULL),
      m_nWidth(0),
      m_nHeight(0),
      m_nBitCount(0)
{
}

CDib::~CDib(void)
{
    Clear();
}

void CDib::Clear()
{
    if (m_lpBits)
    {
        delete [] m_lpBits;
        m_lpBits = NULL;
    }

    if (m_lpPalette)
    {
        delete [] m_lpPalette;
        m_lpPalette = NULL;
    }

    m_nWidth = 0;
    m_nHeight = 0;
    m_nBitCount = 0;
}

BOOL CDib::SaveToFile(LPCTSTR fileName)
{
    CFile file;

    if (!file.Open(fileName, CFile::modeCreate | CFile::modeWrite))
    {
        return FALSE;
    }

    BOOL status = SaveToFile(&file);
    file.Close();
    return status;
}

BOOL CDib::SaveToFile(CFile *pFile)
{
    if (m_lpBits == NULL)
    {
        return FALSE;
    }

    int nByteWidth = BYTE_PER_LINE(m_nWidth, m_nHeight);

    BITMAPFILEHEADER bitmap;
    bitmap.bfType = 'M'*256 + 'B';
    bitmap.bfSize = nByteWidth * m_nHeight;
    bitmap.bfReserved1 = 0;
    bitmap.bfReserved2 = 0;
    bitmap.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    if (m_nBitCount != 24)
    {
        bitmap.bfOffBits += PALETTESIZE(m_nBitCount) * sizeof(RGBQUAD);
    }

    BITMAPINFOHEADER bitmapInfo;
    bitmapInfo.biSize          = sizeof(BITMAPINFOHEADER);
    bitmapInfo.biWidth         = m_nWidth;
    bitmapInfo.biHeight        = m_nHeight;
    bitmapInfo.biPlanes        = 1;
    bitmapInfo.biBitCount      = m_nBitCount;
    bitmapInfo.biCompression   = BI_RGB;
    bitmapInfo.biSizeImage     = 0;
    bitmapInfo.biXPelsPerMeter = 0;
    bitmapInfo.biYPelsPerMeter = 0;
    bitmapInfo.biClrUsed       = 0;
    bitmapInfo.biClrImportant  = 0;

    pFile->Write(&bitmapInfo, sizeof(BITMAPINFOHEADER));

    if (m_nBitCount != 24)
    {
        pFile->Write(m_lpPalette, PALETTESIZE(m_nBitCount) * sizeof(RGBQUAD));
    }
    pFile->Write(m_lpBits, nByteWidth * m_nHeight);

    return TRUE;
}

BOOL CDib::LoadFromFile(LPCTSTR fileName)
{
    CFile file;
    
    if (!file.Open(fileName, CFile::modeRead))
    {
        return FALSE;
    }

    BOOL status = LoadFromFile(&file);
    file.Close();
    return status;
}

BOOL CDib::LoadFromFile(CFile *pFile)
{
    BYTE *lpBitmap;
    BYTE *lpDib;
    int nLen;

    nLen = pFile->GetLength();
    lpBitmap = new BYTE[nLen];

    pFile->Read(lpBitmap, nLen);

    if (lpBitmap[0] != 'B' && lpBitmap[1] != 'M')
    {
        AfxMessageBox(L"It's not a Bitmap!");
        delete [] lpBitmap;
        return FALSE;
    }

    lpDib = lpBitmap + sizeof(BITMAPFILEHEADER);    // add offset
    BOOL status = LoadDib(lpDib);
    delete [] lpBitmap;
    return status;
}

BOOL CDib::LoadDib(BYTE *lpDib)
{
    Clear();
    BYTE *lpBits;
    BITMAPINFOHEADER *pInfo;
    int nWidth, nHeight, nBitCount, nByteWidth;
    RGBQUAD *pPalette;
    unsigned int PaletteSize;

    pInfo = (BITMAPINFOHEADER *)lpDib;
    lpBits = lpDib + sizeof(BITMAPINFOHEADER);

    nWidth = pInfo->biWidth;
    nHeight = pInfo->biHeight;
    nBitCount = pInfo->biBitCount;
    nByteWidth = BYTE_PER_LINE(nWidth, nBitCount);

    switch (nBitCount)
    {
    case 24:
        if (m_lpBits)
        {
            delete [] m_lpBits;
        }
        if (m_lpPalette)
        {
            delete [] m_lpPalette;
            m_lpPalette = NULL;
        }
        m_lpBits = new BYTE[nByteWidth * nHeight];
        memcpy(m_lpBits, lpBits, nByteWidth * nHeight);
        break;
    case 8:
    case 4:
        if (m_lpBits)
        {
            delete [] m_lpBits;
        }
        if (m_lpPalette)
        {
            delete [] m_lpPalette;
        }

        PaletteSize = (1 << pInfo->biBitCount);
        if (pInfo->biClrUsed != 0 && pInfo->biClrUsed < PaletteSize)
        {
            PaletteSize = pInfo->biClrUsed;
        }

        pPalette = (RGBQUAD *)lpBits;
        lpBits += sizeof(RGBQUAD) * PaletteSize;

        m_lpPalette = new BYTE[sizeof(RGBQUAD) * PaletteSize];
        memcpy(m_lpPalette, pPalette, sizeof(RGBQUAD) * PaletteSize);

        m_lpBits = new BYTE[nByteWidth * nHeight];
        memcpy(m_lpBits, lpBits, nByteWidth * nHeight);
        break;
    default:
        return FALSE;
    }

    m_nBitCount = nBitCount;
    m_nWidth = nWidth;
    m_nHeight = nHeight;

    return TRUE;
}

BOOL CDib::SaveToDib(BYTE *lpDib)
{
    if (m_lpBits == NULL)
    {
        return FALSE;
    }

    BYTE *pDib = lpDib;
    int nByteWidth = BYTE_PER_LINE(m_nWidth, m_nBitCount);

    BITMAPINFOHEADER bmpInfo;
    bmpInfo.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.biWidth = m_nWidth;
    bmpInfo.biHeight = m_nHeight;
    bmpInfo.biPlanes = 1;
    bmpInfo.biBitCount = m_nBitCount;
    bmpInfo.biCompression = BI_RGB;
    bmpInfo.biSizeImage = 0;
    bmpInfo.biXPelsPerMeter = 0;
    bmpInfo.biYPelsPerMeter = 0;
    bmpInfo.biClrUsed = 0;
    bmpInfo.biClrImportant = 0;
    memcpy(pDib, &bmpInfo, sizeof(BITMAPINFOHEADER));

    pDib += sizeof(BITMAPINFOHEADER);
    if (m_nBitCount != 24)
    {
        memcpy(pDib, m_lpPalette, PALETTESIZE(m_nBitCount) * sizeof(RGBQUAD));
        pDib += PALETTESIZE(m_nBitCount) * sizeof(RGBQUAD);
    }
    memcpy(pDib, m_lpBits, nByteWidth * m_nHeight);

    return TRUE;
}