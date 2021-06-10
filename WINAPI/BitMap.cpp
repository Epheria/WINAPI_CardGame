#include "BitMap.h"



BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc,char* FileName)
{
	MemDC = CreateCompatibleDC(hdc);
	m_BitMap = (HBITMAP)LoadImageA(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldBitMap = (HBITMAP)SelectObject(MemDC, m_BitMap);
	BITMAP BitMap_Info;
	GetObject(m_BitMap, sizeof(BitMap_Info), &BitMap_Info);
	m_Size.cx = BitMap_Info.bmWidth * 0.5f;
	m_Size.cy = BitMap_Info.bmHeight * 0.5f;
}
void BitMap::Draw(HDC hdc, int x, int y)
{
	StretchBlt(hdc, x, y, m_Size.cx, m_Size.cy, MemDC, 0, 0, m_Size.cx * 2, m_Size.cy * 2, SRCCOPY);
}

BitMap::~BitMap()
{
	SelectObject(MemDC, m_OldBitMap);
	DeleteObject(m_BitMap);
	DeleteDC(MemDC);
}
