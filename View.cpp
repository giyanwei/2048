// View.cpp
#include <stdio.h>
#include "View.h"
#include "resource.h"
#include "Game2048_V0.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("Game 2048");
	HWND		hwnd;
	MSG			msg;
	WNDCLASS	wndclass;

	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName	= TEXT("G2048");
	wndclass.lpszClassName	= szAppName;

	if(!RegisterClass(&wndclass))
	{
		MessageBox (NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName,					// window class name
						TEXT("Game 2048"),			// window caption
						WS_OVERLAPPEDWINDOW,		// window style
						CW_USEDEFAULT,				// initial x position
						CW_USEDEFAULT,				// initial y position
						CW_USEDEFAULT,				// initial x size
						CW_USEDEFAULT,				// initial y size
						NULL,						// parent window handl
						NULL,						// window menu handle
						hInstance,					// program instance handle
						NULL);						// creation parameters
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Game2048 g;
	HDC hdc;
	PAINTSTRUCT	ps;
	static SIZE size;

	switch(message)
	{
	case WM_CREATE:
				WinReSizing(hwnd);
				return 0;
	case WM_SIZE:
				size.cx = LOWORD(lParam);
				size.cy = HIWORD(lParam);
				return 0;
	case WM_PAINT:
				hdc = BeginPaint(hwnd, &ps);
				Draw(hwnd, hdc, size, g);
				EndPaint(hwnd, &ps);
				return 0;
	case WM_COMMAND:								// 处理菜单命令
				switch(LOWORD(wParam))
				{
				case IDM_RESTART:
						// 添加相应语句
						break;
				case IDM_EXIT:
						SendMessage(hwnd, WM_DESTROY, 0, 0);
						break;
				case IDM_HELP:
						MessageBox(hwnd, TEXT("帮助内容（字符串）"), TEXT("帮助"), MB_OK);
						break;
				}
				InvalidateRect(hwnd, NULL, TRUE);	// 使客户区无效，以便重绘视口的内容
				return 0;
	case WM_KEYDOWN:								// 处理键盘消息
				switch(wParam)
				{
				case VK_F1:
						SendMessage(hwnd, WM_COMMAND, IDM_HELP, 0);
						break;
				case VK_ESCAPE:
						{
							int response = MessageBox(hwnd, TEXT("真的退出吗？"), TEXT("Exit"), MB_ICONSTOP|MB_YESNO);
							if(response==IDYES)
								SendMessage(hwnd, WM_DESTROY, 0, 0);
						}
						break;
				case VK_UP:							// 上移
						g.Up();
						InvalidateRect(hwnd, NULL, TRUE);
						break;
				case VK_DOWN:						// 下移
						g.Down();
						InvalidateRect(hwnd, NULL, TRUE);
						break;
				case VK_LEFT:						// 左移
						g.Left();
						InvalidateRect(hwnd, NULL, TRUE);
						break;
				case VK_RIGHT:						// 右移
						g.Right();
						InvalidateRect(hwnd, NULL, TRUE);
						break;
				}
				return 0;
	case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void WinReSizing(HWND hwnd)
{
	int w=500, h=500;
	RECT rc;
	GetClientRect(GetWindow(hwnd, 1), &rc);		// 获取整个操作系统桌面尺寸
	WINDOWPLACEMENT WinPlacement;

	GetWindowPlacement(hwnd, &WinPlacement);
	rc.left = (rc.right-rc.left-w)/2;
	rc.top = (rc.bottom-rc.top-h)/2;
	rc.right = rc.left+w;
	rc.bottom = rc.top+h;
	WinPlacement.rcNormalPosition = rc;
	SetWindowPlacement(hwnd, &WinPlacement);
}

int mylog(int n)
{
	int m, p;
	for(m=0,p=1; p<n; p*=2)
		m++;
	return m;
}

unsigned long ColormapHsv(int n, int Num)		// 仿MatLab的Hsv颜色设置
{
	double x = double(n)/(Num-1);
	int r, g, b;
	if(x<0) x=0; else if(x>1) x=1;
	if(x<3.0/16)
	{
		r = 255;
		g = int(255*(16*x/3));
		if(g<0) g=0; else if(g>255) g=255;
		b = 0;
	}
	else if(x<6.0/16)
	{
		r = int(255*(2-16*x/3));
		if(r<0) r=0; else if(r>255) r=255;
		g = 255;
		b = 0;
	}
	else if(x<8.0/16)
	{
		r = 0;
		g = 255;
		b = int(255*(8*x-3));
		if(b<0) b=0; else if(b>255) b=255;
	}
	else if(x<10.0/16)
	{
		r = 0;
		g = int(255*(5-8*x));
		if(g<0) g=0; else if(g>255) g=255;
		b = 255;
	}
	else if(x<13.0/16)
	{
		r = int(255*(16*x-10)/3);
		if(r<0) r=0; else if(r>255) r=255;
		g = 0;
		b = 255;
	}
	else
	{
		r = 255;
		g = 0;
		b = int(255*(0.9062*(13-16*x)/3+1));
		if(b<0) b=0; else if(b>255) b=255;
	}
	return RGB(r, g, b);
}

COLORREF InvColor(COLORREF color)
{
	return 0xffffff - color;
}

void DrawBlock(HDC hdc, int left, int top, int right, int bottom, int num)
{
	static HFONT hFont = NULL;
	static HPEN hPen = NULL;
	static HBRUSH hBrush = NULL;
	const int LE2048 = 12;				// 不超过2048
	static COLORREF colors[LE2048], invColor;

	for(int i=0; i<LE2048; i++)
		colors[i] = ColormapHsv(i, LE2048);

	int penWidth=2, n, m, w=right-left, h=bottom-top;
	char str[80];

	n = mylog(num);
	sprintf_s(str, "%d", num);
	m = strlen(str);

	invColor = InvColor(colors[n]);
	hPen = CreatePen(PS_SOLID, penWidth, colors[n]);
	hBrush = CreateSolidBrush(invColor);		// 刷背景颜色（补色）
	hFont = CreateFont(	3*h/4, 3*w/(4*m), 0, 0, FW_HEAVY, 0, 0, 0, ANSI_CHARSET,
						OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
//						"Calibri");
//						"Algerian");
						"Stencil");
	SelectObject(hdc, hPen);
	SelectObject(hdc, hBrush);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, colors[n]);
	Rectangle(hdc, left, top, right, bottom);
	if(num!=0)
		TextOut(hdc, left+w/8, top+h/8, str, m);
	DeleteObject(hFont);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void Draw(HWND hwnd, HDC hdc, SIZE size, const Game2048 &g)
{
	RECT rect;
	POINT Orgpt;

	GetClientRect(GetWindow(hwnd, 1), &rect);		// 获取整个操作系统桌面尺寸
	SetMapMode(hdc, MM_ANISOTROPIC);				// 设置映射模式

	SetViewportExtEx(hdc, size.cx, size.cy, NULL);	// 设置窗口、视口范围及视口原点
	SetWindowExtEx(hdc, 2000, 1000, NULL);
	SetViewportOrgEx(hdc, 0, 0, NULL);

	DPtoLP(hdc, (PPOINT)&size, 1);					// 将设备坐标转变为逻辑坐标
	SelectObject(hdc, GetStockObject(BLACK_PEN));
	SetBkMode(hdc, TRANSPARENT);

	GetWindowOrgEx(hdc, &Orgpt);
	LPtoDP(hdc, &Orgpt, 1);							// 将逻辑坐标转换为设备坐标
	GetViewportOrgEx(hdc, &Orgpt);

	int w=size.cx/N, h=size.cy/N;
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
			DrawBlock(hdc, j*w+5, i*h+5, (j+1)*w-5, (i+1)*h-5, g[i][j]);
	}
}
