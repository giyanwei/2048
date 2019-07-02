// View.h
#ifndef MY_VIEW_H
#define MY_VIEW_H

#include <windows.h>
#include <commctrl.h>
#include "Game2048_V0.h"

int mylog(int n);								// �ر�أ�mylog(0)Ϊ0
unsigned long ColormapHsv(int n, int Num);		// ��MatLab��Hsv��ɫ����
COLORREF InvColor(COLORREF color);				// ���ظ�����ɫ�Ĳ�ɫ

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void WinReSizing(HWND hwnd);
void Draw(HWND hwnd, HDC hdc, SIZE size, const Game2048 &g);
void DrawBlock(HDC hdc, int left, int top, int right, int bottom, int num);

#endif
