#pragma warning(disable:4996)
#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

BitMapManager::BitMapManager()
{
	//m_parrBitMap = new BitMap[IMAGE_END];
}


void BitMapManager::Init(HWND hWnd)
{
	char buf[256];
	BitMap* tmp;
	HDC hdc = GetDC(hWnd);
	for (int i = IMAGE_START; i <= IMAGE_END; i++)
	{
		sprintf(buf, "Resource//0%d.bmp", i);
		tmp = new BitMap;
		tmp->Init(hdc,buf);
		m_parrBitMap.push_back(tmp);
	}
	ReleaseDC(hWnd, hdc);
}

BitMapManager::~BitMapManager()
{
	for (auto& b : m_parrBitMap)
	{
		delete b;
	}
	//delete[] m_parrBitMap;
}
