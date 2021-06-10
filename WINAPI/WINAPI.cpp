// WinAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinAPI.h"
#include "Card.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);





int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }


    ULONGLONG frameTime, limitFrameTime = GetTickCount64();
    ULONGLONG time = 0;

    HDC hdc = GetDC(g_hWnd);


    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    // 기본 메시지 루프입니다:
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            frameTime = GetTickCount64();       //윈도우가 시작된 후 지금까지 시간. 1/1000초.
            if (limitFrameTime <= frameTime)  //0.03초마다 업데이트.
            {
                float elapsed = (frameTime - limitFrameTime) * 0.01f; //유저의 시스템 환경에 따라 발생하는 시간차이.
                limitFrameTime = frameTime + 30;//30 => 0.03초.
            }
        }
    }
    ReleaseDC(g_hWnd, hdc);

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_WINAPI); 메뉴 바를 사용하지 않음.
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
    //WS_OVERLAPPEDWINDOW
    //WS_OVERLAPPED  :0값을 가지므로 의미가 없다.
    //WS_CAPTION     :타이틀 바를 가진다.
    //WS_SYSMENU     :시스템 메뉴를 가진다.
    //WS_MINIMIZEBOX :최소화 버튼을 가진다.
    //WS_MAXIMIZEBOX :최대화 버튼을 가진다.
    //WS_THICKFRAME  :크기조절을 가능하게 한다.
    HWND hWnd = g_hWnd = CreateWindowW(szWindowClass, L"타이틀 이름!!", WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


    if (!hWnd)
    {
        return FALSE;
    }

    //-----------------------------------------------------------
    // 윈도우 작업영역을 화면의 중앙에 맞추기 위해 코드 추가.
    //RECT rcWinBounds;
    //if (GetWindowRect(hWnd, &rcWinBounds))
    //{
    //    int nScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);  //SM_CXFULLSCREEN:전체화면의 너비.
    //    int nScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN); //SM_CYFULLSCREEN:전체화면의 높이.
    //                                                           //테스크바에의해 영향을 받기 때문에 그게 싫다면,
    //                                                           //SM_CXSCREEN, SM_CYSCREEN을 사용하면 된다.
    //    int nWidth = rcWinBounds.right - rcWinBounds.left;
    //    int nHeight = rcWinBounds.bottom - rcWinBounds.top;
    //    int fDestX = static_cast<int>((nScreenWidth - nWidth) * 0.5f);
    //    int fDestY = static_cast<int>((nScreenHeight - nHeight) * 0.5f);
    //
    //    MoveWindow(hWnd, fDestX, fDestY, nWidth, nHeight, true);
    //}
    //-----------------------------------------------------------

    //SetWindowText(hWnd, L"타이틀 이름!!");

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

Card card;
std::vector<Card> CardList;
Card card2;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    POINT Point;
    int ix = 100, iy = 100;
    switch (message)
    {
    ////그리기는 게임루프에서 처리.
    case WM_CREATE:
        BitMapManager::GetInstance()->Init(hWnd);
        for (int i = IMAGE_DOG; i < IMAGE_CHICKEN; i++)
        {
            card.Init((IMAGE)i, ix, iy);
            ix += 200;
            // iy += 200;
            CardList.push_back(card);
        }
        //card.Init(IMAGE_CHICKEN, 100, 100);
        //card2.Init(IMAGE_DOG, 300, 100);
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            for (auto& c : CardList)
            {
                c.Draw(hdc);
            }
            //card.Draw(hdc);
            //card2.Draw(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_LBUTTONDOWN:
        Point.x = LOWORD(lParam);
        Point.y = HIWORD(lParam);
        for (auto& c : CardList)
        {
            if (c.ColliderCheck(Point))
            {
                InvalidateRect(hWnd, NULL, true);
                break;
            }
        }
        //if (card.ColliderCheck(Point))
        //    InvalidateRect(hWnd, NULL, true);
        break;
    case WM_KEYDOWN:
    {
        //esc 키를 누르면 어플리케이션 종료하겠다.
        if (VK_ESCAPE == wParam)
        {
            PostQuitMessage(0);
        }
    }
    break;
    case WM_DESTROY:
        delete BitMapManager::GetInstance();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}