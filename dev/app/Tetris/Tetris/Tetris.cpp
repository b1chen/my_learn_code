// Tetris.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Tetris.h"
#include "item.h"

#define MAX_LOADSTRING 100


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TETRIS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
	// Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TETRIS));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TETRIS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNSHADOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TETRIS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   int screenwide, screenhight;
   screenwide = GetSystemMetrics(SM_CXFULLSCREEN); //获取屏幕宽度，即横向分辨率
   screenhight = GetSystemMetrics(SM_CYFULLSCREEN); //获取屏幕高度
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
	   (screenwide - (W + W1)*BSIZE) / 2, (screenhight - H*BSIZE) / 2, (W + W1 + 3)*BSIZE, (H + 3)*BSIZE+5, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   
   SetTimer(hWnd, 1, 500, 0);
   //MessageBox(hWnd, L" Cb制作", L"开始", MB_OK); //弹出框
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HPEN hpen = CreatePen(PS_SOLID, 1, BgColor); //选择画刷，用背景色作画刷
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			srand(time(NULL));
			if (!Map::cur_block_exist) {
				Map::current_block = Map::RandomOne();
				Map::next_block = Map::RandomOne();
				Map::cur_block_exist = true;
				
			}
			
			TextOut(hdc, (14 + 3)*BSIZE + 5, (10 + 0)*BSIZE + 5, TEXT("score"), strlen("score"));
			std::wstring str = std::to_wstring(Map::score);
			TextOut(hdc, (14 + 3)*BSIZE + 5, (10 + 1)*BSIZE + 5, str.c_str(), str.length());

			TextOut(hdc, (14 + 3)*BSIZE + 5, (12 + 0)*BSIZE + 5, TEXT("level"), strlen("level"));
			std::wstring str2 = std::to_wstring(Map::level);
			TextOut(hdc, (14 + 3)*BSIZE + 5, (12 + 1)*BSIZE + 5, str2.c_str(), str2.length());

			Map::paint_map(hdc, hpen); //调用Paint函数绘制界面
			Map::paint_block(hdc, hpen, *Map::current_block);
			Map::paint_next_block(hdc, hpen, *Map::next_block);
			EndPaint(hWnd, &ps);
			//MessageBox(hWnd, L" Cb制作", L"开始", MB_OK); //弹出框
			
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_TIMER:
		{
			HDC hdc = GetDC(hWnd);
			if (Map::gameover == 1) break;
			bool wall_flag = false;
			if (Map::cur_block_exist) {
				//if (!(Map::current_block)->is_out_of_bound())
				
				if (!(Map::current_block)->can_drop()) {
					Map::set_block_to_map(*(Map::current_block));
					wall_flag = true;
					//std::vector<int> full_lines = Map::detect_full_lines();
					//Map::update_map(full_lines);
				}
				else {
					(Map::current_block)->move_down();
				}
			}
			else {
				Map::current_block = Map::RandomOne();
				Map::next_block = Map::RandomOne();
				Map::cur_block_exist = true;
			}
			Map::paint_map(hdc, hpen); //调用Paint函数绘制界面
			
			if (!wall_flag) {
				Map::paint_block(hdc, hpen, *Map::current_block);
			}
			else {
				std::vector<int> full_lines = Map::detect_full_lines();
				Map::update_map(full_lines);
				delete Map::current_block;
				Map::current_block = nullptr;
				Map::cur_block_exist = false;
				
				Map::current_block = Map::next_block;

				if (((Map::current_block)->is_out_of_bound()) || ((Map::current_block)->coincide())) {
					//MessageBox(hWnd, L" game", L"over timer", MB_OK); //弹出框;
					KillTimer(hWnd, 1);
					Map::gameover = 1;
					break;
				}

				Map::next_block = Map::RandomOne();
				Map::cur_block_exist = true;
			}
			Map::paint_next_block(hdc, hpen, *Map::next_block);
			std::wstring str = std::to_wstring(Map::score);
			TextOut(hdc, (14 + 3)*BSIZE + 5, (10 + 1)*BSIZE + 5, str.c_str(), str.length());
			if (Map::score > 500 * Map::level) {
				SetTimer(hWnd, 1, (500 - Map::level * 100) < 100 ? 100 : (500 - Map::level), 0);
				Map::level++;
			}
			
			ReleaseDC(hWnd, hdc);
		}
		break;
	case WM_KEYDOWN:
		{
			HDC hdc = GetDC(hWnd);
			if (Map::gameover == 1) break;
			if ((Map::timer_flag) && ((int)wParam != VK_SPACE)) {
				break;
			}
			switch ((int)wParam) {
				case VK_UP:
					{
						if (Map::cur_block_exist) {
							(Map::current_block)->rotate_left();
							if (((Map::current_block)->is_out_of_bound()) || ((Map::current_block)->coincide()))
								(Map::current_block)->rotate_right();
						}
						Map::paint_map(hdc, hpen); //调用Paint函数绘制界面
						Map::paint_block(hdc, hpen, *Map::current_block);
						Map::paint_next_block(hdc, hpen, *Map::next_block);
						ReleaseDC(hWnd, hdc);
					}
					break;
				case VK_DOWN:
					{
						bool wall_flag = false;

						if (Map::cur_block_exist) {
							if (!(Map::current_block)->can_drop()) {
								Map::set_block_to_map(*(Map::current_block));
								wall_flag = true;
							}
							else {
								(Map::current_block)->move_down();
							}
						}
						else {/*
							Map::current_block = Map::RandomOne();
							Map::next_block = Map::RandomOne();
							Map::cur_block_exist = true;
							*/
							break;
						}
					
						Map::paint_map(hdc, hpen); //调用Paint函数绘制界面

						if (!wall_flag) {
							Map::paint_block(hdc, hpen, *Map::current_block);
						}
						else {
							std::vector<int> full_lines = Map::detect_full_lines();
							Map::update_map(full_lines);
							delete Map::current_block;
							Map::current_block = nullptr;
							Map::cur_block_exist = false;

							Map::current_block = Map::next_block;
							if (((Map::current_block)->is_out_of_bound()) || ((Map::current_block)->coincide())) {
								Map::gameover = 1;
								//MessageBox(hWnd, L" game", L"over", MB_OK); //弹出框;
								MessageBox(hWnd, L"game over", L"information", MB_OK); //弹出框;
								KillTimer(hWnd, 1);
								
								break;
							}
							Map::next_block = Map::RandomOne();
							Map::cur_block_exist = true;
						}
						Map::paint_next_block(hdc, hpen, *Map::next_block);
						std::wstring str = std::to_wstring(Map::score);
						TextOut(hdc, (14 + 3)*BSIZE + 5, (10 + 1)*BSIZE + 5, str.c_str(), str.length());

						ReleaseDC(hWnd, hdc);
					}
					break;
				case VK_LEFT:
					if (Map::cur_block_exist) {
						(Map::current_block)->move_left();
						if ((Map::current_block)->is_out_of_bound() || (Map::current_block)->coincide())
							(Map::current_block)->move_right();
					}
					else {
						ReleaseDC(hWnd, hdc);
						break;
					}
					Map::paint_map(hdc, hpen); //调用Paint函数绘制界面
					Map::paint_block(hdc, hpen, *Map::current_block);
					Map::paint_next_block(hdc, hpen, *Map::next_block);
					ReleaseDC(hWnd, hdc);
					break;
				case VK_RIGHT:
					if (Map::cur_block_exist) {
						(Map::current_block)->move_right();
						if ((Map::current_block)->is_out_of_bound() || (Map::current_block)->coincide())
							(Map::current_block)->move_left();
					}
					else {
						ReleaseDC(hWnd, hdc);
						break;
					}
					Map::paint_map(hdc, hpen); //调用Paint函数绘制界面
					Map::paint_block(hdc, hpen, *Map::current_block);
					Map::paint_next_block(hdc, hpen, *Map::next_block);
					ReleaseDC(hWnd, hdc);
					break;
				case VK_SPACE:
					Map::timer_flag = (++(Map::timer_flag))%2;
					if (Map::timer_flag) {
						KillTimer(hWnd, 1);
					}
					else {
						SetTimer(hWnd, 1, 500, 0);
					}
					
				default:
					break;
			}
		}
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
