#include "pch.h"
#include "framework.h"
#include "GameCoding.h"
#include "Game.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
    // _In, _In_opt_ : 뒤에 오는 것에 대한 힌트(주석 느낌). 없어도 작동합니다.
{
    // TODO: 여기에 코드를 입력합니다.

    /** 중요 목록 */
    // 1. MyRegisterClass   : 윈도우 창 정보 등록
    // 2. InitInstance      : 윈도우 창 생성
    // 3. Main Loop         : 메인 루프

    // * MyRegisterClass()에 윈도우 창 정보를 등록하고, InitInstance()에서 해당 정보를 기반으로 윈도우 창을 만드는 개념입니다.
    // * InitInstance()로 창을 만들고 Main Loop에서 반복해 실행하는 방식으로 진행합니다.

    /** 1. MyRegisterClass (윈도우 창 정보 등록 )*/
    MyRegisterClass(hInstance);

    /** 2. InitInstance (윈도우 창 생성) */ 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 게임 객체를 생성합니다.
    Game game;

    // 객체를 초기화합니다.
    // * Init() 함수의 경우 HWND를 매개변수로 전달 받습니다.
    // * HWND는 InitInstance() 함수에서 생성하고 초기화됩니다.
    // ** Init()함수에 전달하기 위해 전역으로 빼서 관리합니다.
    game.Init(g_hWnd);

    MSG msg = {};

    // 프레임을 조절하는 방법
    // * 먼저 시간을 저장하기 위한 변수를 하나 선언합니다.
    // * while()문 안에서 GetTickCount64()를 통해 시간을 전달받고, 특정 시간이 경과할 때마다 프레임을 업데이트하게 설정합니다.
    uint64 prevTick = 0;

    /** 3. Main Loop (메인 루프) */
    // 게임은 항상 무한 루프에서 동작합니다.
    // * 윈도우즈 방식이 기본적으로 실행되는 프로그램이 많으므로 메시지(일감)라는 개념을 등장시켜 어떤 메시지를 넣어준 다음 순차적으로 실행해주는 개념입니다.
    // * 메시지 큐에서 메시지가 존재한다면 해당 메시지를 처리하는 방식으로 반복합니다. (처리하는 함수 : WndProc)
    // * 즉, GetMessage()를 통해 메시지가 있는 경우에 해당 메시지를 처리하는 방식으로 동작합니다.
    
    // * message가 WM_QUIT이 아닌 경우에 무한히 반복합니다.
    while (msg.message != WM_QUIT)
    {
        // 일반적인 상황(즉, 메시지가 들어오는 상황)이라면?
        // * PeekMessage : 메시지가 없으면 false를 반환, 있으면 true를 반환하는 함수입니다.
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            // 메시지를 처리하는 부분입니다.
            ::DispatchMessage(&msg);
        }
        // 메시지가 들어오지 않는 상황이라면?
        else
        {
            uint64 now = ::GetTickCount64();

            //if (now - prevTick >= 20)
            {
                // 게임 로직을 실행합니다.
                // * 만들어둔 게임 로직을 추가합니다.
                game.Update();
                game.Render();

                prevTick = now;
            }
        }

        /**
        - 메시지가 들어오는 상황에만 일반적으로 처리하고 아닌 상황에는 게임 로직을 실행하도록 설정하였습니다.
        
        - Q) 메시지가 들어오는 일반적인 상황이라면 게임 로직을 실행하지 않는가? 
        - A) 메시지가 들어오는 순간이 그렇게 많지 않고 Loop는 1초에 몇 만번씩 호출되므로 문제가 없습니다.
             + 아니라면 else문을 제거하고 아래에 게임 로직을 실행시켜 모든 경우에서 돌아가도록 설정할 수도 있습니다.
        */
    }

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    // 메인 루프에서 처리할 메시지를 WndProc를 통해 처리하라는 의미입니다.
    // * 즉, 처음 등록할 때 메시지를 받아 WndProc 함수를 통해 처리하라는 의미의 콜백 함수입니다.
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMECODING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);

    // 메뉴 옵션입니다. 사용하지 않을 것이면 nullptr 처리해주면 됩니다.
    wcex.lpszMenuName   = nullptr; //MAKEINTRESOURCEW(IDC_GAMECODING);
    // szWindowClass 대신 직접 L을 붙여 클래스 이름을 지정할 수 있습니다.
    wcex.lpszClassName  = L"GameCoding";// szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   // MyRegisterClass() 함수에서 설정한 내용을 기반으로 윈도우 창을 생성합니다.
   // * szWindowClass 대신 다른 클래스 이름을 사용할 것이므로 동일하게 설정합니다.
   // * szTitle 대신 Client 이름을 창 이름으로 설정합니다.
   // * CW_USEDEFAULT, 0 : 시작 위치
   // * CW_USEDEFAULT, 0 : 창의 크기 (실습을 위해 800 * 600으로 변경합니다.)
   // ** 창의 크기 같은 경우에는 맨 위에 출력되는 메뉴까지 포함되는 크기입니다.
   // ** 정확하게 사용하는 공간의 크기를 800 * 600으로 설정해주기 위해 AdjustWindowRect()함수를 실행시킵니다.
   RECT windowRect = { 0, 0, 800, 600 };
   ::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

   HWND hWnd = CreateWindowW(L"GameCoding", L"Client", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, hInstance, nullptr);

   // 만들어둔 전역 변수에 hWnd(핸들 번호)를 저장합니다.
   g_hWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ::ShowWindow(hWnd, nCmdShow);
   ::UpdateWindow(hWnd);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            // * 메시지의 번호에 따라 동작을 수행합니다.
            switch (wmId)
            {
            // case IDM_ABOUT:
            //     DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            //     break;
            case IDM_EXIT:
                ::DestroyWindow(hWnd);
                break;
            default:
                return ::DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    // 그리는 것과 관련있는 핵심 이벤트 중 하나입니다.
    // * WM_PAINT는 창의 크기가 달라지거나 창을 내렸다 다시 올리는 경우 호출됩니다.
    // * 즉, 게임의 경우 매 프레임마다 그려지는 것이 달라져야 하므로 이와 같은 기본적인 골격 방식으로 게임을 만들 수 없습니다.
    case WM_PAINT:
        {
            PAINTSTRUCT ps;

            // hdc : 도화지의 number
            HDC hdc = ::BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            ::EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
        ::PostQuitMessage(0);
        break;
    default:
        return ::DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
// * 예를들면 단축키를 눌렀을 때 정보를 보여주는 기능을 합니다.
// * 하지만, 지금은 모두 사용하지 않기 때문에 삭제해도 아무런 상관이 없습니다.
// INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
// {
//     UNREFERENCED_PARAMETER(lParam);
//     switch (message)
//     {
//     case WM_INITDIALOG:
//         return (INT_PTR)TRUE;
// 
//     case WM_COMMAND:
//         if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//         {
//             EndDialog(hDlg, LOWORD(wParam));
//             return (INT_PTR)TRUE;
//         }
//         break;
//     }
//     return (INT_PTR)FALSE;
// }
