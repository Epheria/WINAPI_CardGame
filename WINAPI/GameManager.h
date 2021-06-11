#pragma once
#include<Windows.h>
#include <string>
#include <time.h>
#include "Card.h"

class GameManager
{
private:
	Card m_Card;
	Card m_BackGround;
	std::vector<Card> CardList;
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

	void DrawMenu(HWND hWnd, HDC hdc, PAINTSTRUCT ps);
	void DrawCard(HWND hWnd, HDC hdc);
	void CreateCard(HWND hWnd);
	void Update(HWND hWnd, LPARAM lParam);
	void Draw(HWND hWnd, LPARAM lParam, HDC hdc, PAINTSTRUCT ps);
};

