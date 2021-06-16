#pragma once
#include<Windows.h>
#include <string>
#include <time.h>
#include "Card.h"

#define MAX_CARD 10
#define MAX_CARDLIST 20
#define GAME_MENU  -1
#define GAME_PLAY  1

class GameManager
{
private:
	bool m_bPlayStatus;
	int m_iWinCount;
	int m_iLeftTime;
	Card m_Card;
	Card m_BackGround;
	std::vector<Card> CardList;
	std::vector<Card> CardBuffer;
	std::vector<IMAGE> ImageList;
	int m_index, m_index2;
	int iCurtime;
	static GameManager* m_hThis;
	RECT rect = { 249, 200, 329, 250 };
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
	inline int GetWinCount()
	{
		return m_iWinCount;
	}
	inline int GetLeftTime()
	{
		return m_iLeftTime;
	}
	inline void UpdateLeftTime()
	{
		if(m_iLeftTime >= 0)
			m_iLeftTime--;
	}
	inline bool GetPlayStatus()
	{
		return m_bPlayStatus;
	}
	inline void InitPlayStatus()
	{
		m_bPlayStatus = false;
	}
	void DrawCardRear(HWND hWnd);
	void DrawMenu(HWND hWnd, HDC hdc, PAINTSTRUCT ps);
	void DrawCard(HWND hWnd, HDC hdc);
	void CreateCard(HWND hWnd);
	void Update(HWND hWnd, LPARAM lParam);
	void Draw(HWND hWnd, LPARAM lParam, HDC hdc, PAINTSTRUCT ps);
	void RandCard();
	bool CheckWin();
	bool GameOver();

};

