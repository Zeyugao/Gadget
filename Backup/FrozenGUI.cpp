// FrozenGUI.cpp : ����Ӧ�ó������ڵ㡣
//


#include "stdafx.h"

#include "FrozenGUI.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FROZENGUI, szWindowClass, MAX_LOADSTRING);
	//ע�ᴰ����
	{
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FROZENGUI));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = szWindowClass;
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		RegisterClassExW(&wcex);
		wcex.lpfnWndProc = DialogProc;
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = TEXT("Setting");

		RegisterClassExW(&wcex);
	}
	// ִ��Ӧ�ó����ʼ��: 
	{
		hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

		int nWidth, nHeight;

		nWidth = 500;
		nHeight = 400;

		HWND hWnd = CreateWindowExW(0, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX),
			0, 0, nWidth, nHeight, nullptr, nullptr, hInst, nullptr);
		if (!hWnd)
		{
			return FALSE;
		}
		RECT WindowRect, ClientRect;
		GetWindowRect(hWnd, &WindowRect);
		GetClientRect(hWnd, &ClientRect);

		nWidth += (WindowRect.right - WindowRect.left) - (ClientRect.right - ClientRect.left);
		nHeight += (WindowRect.bottom - WindowRect.top) - (ClientRect.bottom - ClientRect.top);

		int nX = (GetSystemMetrics(SM_CXSCREEN) - nWidth) / 2;
		int nY = (GetSystemMetrics(SM_CYSCREEN) - nHeight) / 2;
		SetWindowPos(hWnd, nullptr, nX, nY, nWidth, nHeight, 0);

		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
	}

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FROZENGUI));

    MSG msg;

    // ����Ϣѭ��: 
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
void GetFont(HFONT &hFont,int nHeight,TCHAR*szFaceName) {
	hFont = CreateFont(nHeight, 0, 0, 0, 0, false, false, false,
		CHINESEBIG5_CHARSET, OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
		FF_MODERN, szFaceName);
}
void CreateButton(TCHAR*szWindowName,HFONT hFont, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu) {
	HWND hWnd = CreateWindow(L"BUTTON", szWindowName, WS_CHILD | WS_VISIBLE, x, y, nWidth, nHeight, hWndParent, hMenu, nullptr, nullptr);
	SendMessage(hWnd, WM_SETFONT, (LPARAM)hFont, TRUE);
}

void DisplayModelDialog(HWND hWndParent) {
	EnableWindow(hWndParent, FALSE);
	
	{

		int nWidth, nHeight;

		nWidth = 300;
		nHeight = 200;

		HWND hWnd = CreateWindowExW(0, L"Setting", szTitle, WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX),
			0, 0, nWidth, nHeight, hWndParent, nullptr, hInst, nullptr);
		if (!hWnd)
		{
			return;
		}
		RECT WindowRect, ClientRect;
		GetWindowRect(hWnd, &WindowRect);
		GetClientRect(hWnd, &ClientRect);

		nWidth += (WindowRect.right - WindowRect.left) - (ClientRect.right - ClientRect.left);
		nHeight += (WindowRect.bottom - WindowRect.top) - (ClientRect.bottom - ClientRect.top);

		int nX = (GetSystemMetrics(SM_CXSCREEN) - nWidth) / 2;
		int nY = (GetSystemMetrics(SM_CYSCREEN) - nHeight) / 2;
		SetWindowPos(hWnd, nullptr, nX, nY, nWidth, nHeight, 0);

		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
	}

	//HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FROZENGUI));

	MSG msg;

	// ����Ϣѭ��: 
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		//if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	EnableWindow(hWndParent, TRUE);
	SetForegroundWindow(hWndParent);
}
LRESULT CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_BTN2:
		{
			MessageBox(hWnd, L"MessageBox", L"", MB_OK);
		}
		break;
		default:
			break;
		}
	}
	break;
	case WM_CREATE:
	{
		HFONT hFont;
		GetFont(hFont, 20, L"΢���ź�");
		CreateButton(L"MessageBox", hFont, 300 - 120, 200 - 50, 100, 30, hWnd, (HMENU)ID_BTN2);
		int  i = GetLastError();
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �����˵�ѡ��: 
            switch (wmId)
            {
			case ID_BTN1:
			{
				DisplayModelDialog(hWnd);
			}
			break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_SHOWWINDOW:
	{
		HFONT hFont;
		GetFont(hFont, 20, L"΢���ź�");
		CreateButton(L"����", hFont, 500 - 60, 400 - 50, 40, 30, hWnd, (HMENU)ID_BTN1);
	}
	break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
