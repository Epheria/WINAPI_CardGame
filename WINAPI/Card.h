#pragma once
#include"BitMap.h"
#include"BitMapManager.h"
enum CARD
{
	CARD_FRONT,
	CARD_REAR,
	CARD_END
};

class Card
{
private:
	CARD m_eCardState;
	BitMap* m_pBitMap[CARD_END];
	int m_ix;
	int m_iy;
	RECT m_BitMapRect;
public:
	Card();
	inline BitMap* GetCardImage()
	{
		return m_pBitMap[CARD_FRONT];
	}
	inline void DrawCardEnd()
	{
		m_eCardState = CARD_END;
	}
	void Init(IMAGE Index, int x, int y);
	void InitBackGround(IMAGE Index, int x, int y);
	void Draw(HDC hdc);
	void DrawBackGround(HDC hdc);
	bool ColliderCheck(POINT point);
	~Card();
};

