#pragma once
#include<Windows.h>
#include <string>
#include <time.h>
#include "Card.h"

#define MAX_CARD 10
#define MAX_CARDLIST 20

class GameManager
{
private:
	int m_iWinCount;
	Card m_Card;
	Card m_BackGround;
	std::vector<Card> CardList;
	std::vector<Card> CardBuffer;
	std::vector<IMAGE> ImageList;
	int m_index, m_index2;
	int iCurtime;
	static GameManager* m_hThis;
	RECT rect = { 100, 100, 400, 300 };
	int m_iMenuSelect;
public:
	static GameManager* GetInstance()
	{
 		if (m_hThis == NULL)
			m_hThis = new GameManager;
		return m_hThis;
	}
	GameManager();
	~GameManager();
	IMAGE GetImage(int index)
	{
		return ImageList[index];
	}
	bool IsSameCard(int index)
	{
		if (-1 != m_index)
		{
			return (CardList[index].GetCardImage() == CardList[m_index].GetCardImage());
		}

		return false;
	}
	void DrawCardRear(HWND hWnd);
	void DrawMenu(HWND hWnd, HDC hdc, PAINTSTRUCT ps);
	void DrawCard(HWND hWnd, HDC hdc);
	void CreateCard(HWND hWnd);
	void Update(HWND hWnd, LPARAM lParam);
	void Draw(HWND hWnd, LPARAM lParam, HDC hdc, PAINTSTRUCT ps);
	void RandCard();

};

