#include "GameManager.h"
GameManager* GameManager::m_hThis = NULL;

GameManager::GameManager()
{
    m_iWinCount = 0;
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
    int i = 0;
    RandCard();
    BitMapManager::GetInstance()->Init(hWnd);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            m_Card.Init(GetImage(i), x * (73 + 10) + 80, y * (118 + 10) + 140);
            CardList.push_back(m_Card);
            i++;
        }
     }

    m_BackGround.InitBackGround(IMAGE_END, 0, 0);
}

void GameManager::RandCard()
{
    srand(time(NULL));
    std::vector<IMAGE> CompareList;

    for (int i = 0; i < MAX_CARD; i++)
    {
        CompareList.push_back((IMAGE)i);
        CompareList.push_back((IMAGE)i);
    }

    while (!CompareList.empty())
    {
        int index = rand() % (int)(CompareList.size());
        auto iter = CompareList.begin() + index;
        ImageList.push_back(CompareList[index]);
        CompareList.erase(iter);
    }
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
                // Card를 보내지말고 index 를 보내서 인덱스값으로 비교하면될듯
                // for(int i = 0; ....) 이런식
                if (IsSameCard(c))
                {
                    m_iWinCount++;
                }
               
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
