#include "GameManager.h"
GameManager* GameManager::m_hThis = NULL;

GameManager::GameManager()
{
    m_iMenuSelect = -1;
}

void GameManager::DrawMenu(HWND hWnd, HDC hdc, PAINTSTRUCT ps)
{
    POINT Point;
    DrawTextA(hdc, "게임시작", -1, &rect, DT_CENTER | DT_WORDBREAK);
}

void GameManager::DrawCard(HWND hWnd, HDC hdc)
{
    m_BackGround.DrawBackGround(hdc);

    for (auto& c : CardList)
    {
        c.Draw(hdc);
    }
}

void GameManager::CreateCard(HWND hWnd)
{
    srand(time(NULL));
    
    int ix = 40, iy = 100;
    int iCur = 0;

    int i = 0;
    BitMapManager::GetInstance()->Init(hWnd);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            m_Card.Init((IMAGE)i, x * (73 + 10) + 80, y * (118 + 10) + 140);
            CardList.push_back(m_Card);
            
        }
        //m_Card.Init((IMAGE)i, ix, iy);
        //ix += 100;
        //if (iCur % 5 >= 5 || iCur % 10 >= 5)
        //    iy += 100;
        //CardList.push_back(m_Card);
        //iCur++;
        i++;
    }

    m_BackGround.InitBackGround(IMAGE_END, 0, 0);
}

void GameManager::Update(HWND hWnd, LPARAM lParam)
{
    POINT Point;
    Point.x = LOWORD(lParam);
    Point.y = HIWORD(lParam);

    switch (m_iMenuSelect)
    {
    case 1:
        for (auto& c : CardList)
        {
            if (c.ColliderCheck(Point))
            {

                InvalidateRect(hWnd, NULL, true);
                break;
            }
        }
        break;
    case -1:
        if (PtInRect(&rect, Point))
        {
            m_iMenuSelect = 1;
            InvalidateRect(hWnd, NULL, true);
        }
        break;
    }
}

void GameManager::Draw(HWND hWnd, LPARAM lParam, HDC hdc, PAINTSTRUCT ps)
{
    switch (m_iMenuSelect)
    {
    case 1:
        GameManager::GetInstance()->DrawCard(hWnd, hdc);
        break;
    case -1:
        GameManager::GetInstance()->DrawMenu(hWnd, hdc, ps);
    }
}

GameManager::~GameManager()
{
}
