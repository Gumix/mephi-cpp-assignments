#include "stdafx.h"
#include "lab6.h"

const int XMAX = 400;
const int YMAX = 400;

HPEN hGrayPen, hGreenPen;
void (*Functions[5])(float, int *, int *);
int nFunction = 0;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{ 
	DialogBox(hInst, (LPCWSTR)DIALOG, NULL, DlgProc); 
	return 0;
} 

BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{ 
	switch(msg)
	{
		HANDLE_MSG(hwnd, WM_INITDIALOG, DlgOnInitDialog); 
		HANDLE_MSG(hwnd, WM_COMMAND, DlgOnCommand); 
		HANDLE_MSG(hwnd, WM_PAINT, DlgOnPaint); 
	default:
		return FALSE;
	}
}

BOOL DlgOnInitDialog(HWND hwnd, HWND, LPARAM)
{
	hGrayPen = CreatePen(PS_SOLID, 1, RGB(200,200,200));
	hGreenPen = CreatePen(PS_SOLID, 2, RGB(0,100,0));

	SendDlgItemMessage(hwnd, IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)L"Архимедова спираль");
	SendDlgItemMessage(hwnd, IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)L"Каннабис");
	SendDlgItemMessage(hwnd, IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)L"Луна");
	SendDlgItemMessage(hwnd, IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)L"Фигура Лиссажу");
	SendDlgItemMessage(hwnd, IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)L"Эпициклоида");

	Functions[0] = fArchimedeanSpiral;
	Functions[1] = fCannabis;
	Functions[2] = fMoon;
	Functions[3] = fLissajousCurve;
	Functions[4] = fEpicycloid;

	return TRUE;
}

void DlgOnCommand(HWND hwnd, int id, HWND, UINT CodeNotify)
{ 
	switch(id)
	{
	case IDC_COMBO1:
		if (CodeNotify == CBN_SELCHANGE)
			nFunction = SendDlgItemMessage(hwnd, IDC_COMBO1, CB_GETCURSEL, 0, 0);
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case IDCANCEL:
		EndDialog(hwnd, 0);
	}
}

void DlgOnPaint(HWND hwnd)
{
	PAINTSTRUCT ps; 
	HDC hdc = BeginPaint(hwnd, &ps);

	SelectPen(hdc, hGrayPen);

	for (int i = 50; i < XMAX/2; i += 50)
	{
		MoveToEx(hdc, XMAX/2 + i, 10, NULL); 
		LineTo(hdc, XMAX/2 + i, YMAX-10);
		MoveToEx(hdc, XMAX/2 - i, 10, NULL); 
		LineTo(hdc, XMAX/2 - i, YMAX-10);
		MoveToEx(hdc, 10, YMAX/2 + i, NULL); 
		LineTo(hdc, XMAX-10, YMAX/2 + i);
		MoveToEx(hdc, 10, YMAX/2 - i, NULL); 
		LineTo(hdc, XMAX-10, YMAX/2 - i);
	}
	
	SelectPen(hdc, GetStockPen(BLACK_PEN));
 
	MoveToEx(hdc, 5, 5, NULL); 
	LineTo(hdc, XMAX-5, 5);
	MoveToEx(hdc, 5, YMAX-5, NULL); 
	LineTo(hdc, XMAX-5, YMAX-5);
	MoveToEx(hdc, 5, 5, NULL); 
	LineTo(hdc, 5, YMAX-5);
	MoveToEx(hdc, XMAX-5, 5, NULL); 
	LineTo(hdc, XMAX-5, YMAX-5);

	MoveToEx(hdc, 10, YMAX/2, NULL); 
	LineTo(hdc, XMAX-10, YMAX/2);
	MoveToEx(hdc, XMAX/2, 10, NULL);
	LineTo(hdc, XMAX/2, YMAX-10);

	SelectPen(hdc, hGreenPen);

	int x, y;
	Functions[nFunction](0, &x, &y);
	MoveToEx(hdc, XMAX/2 + x, XMAX/2 - y, NULL); 

	for (float t = 0.01; t < 20; t += 0.01)
	{
		Functions[nFunction](t, &x, &y);
		LineTo(hdc, XMAX/2 + x, XMAX/2 - y);
	}

	EndPaint(hwnd, &ps);
}

void fArchimedeanSpiral(float t, int *x, int *y)
{
	double R = 5*t;
	*x = R * cos(t) + 0.5;
	*y = R * sin(t) + 0.5;
}

void fCannabis(float t, int *x, int *y)
{
	double R = (1+sin(t)) * (1+0.9*cos(8*t)) * (1+0.1*cos(24*t));
	R *= 40;
	*x = R * cos(t) + 0.5;
	*y = R * sin(t) + 0.5;
}

void fMoon(float t, int *x, int *y)
{
	double R = 3 + sin(t);
	R *= 20;
	double ph = 2*cos(t);
	*x = R * cos(ph) + 0.5;
	*y = R * sin(ph) + 0.5;
}

void fLissajousCurve(float t, int *x, int *y)
{
	int R = 120;
	*x = R * cos(1.5*t) + 0.5;
	*y = R * sin(t) + 0.5;
}

void fEpicycloid(float t, int *x, int *y)
{
	double r = 40;
	double R = 60;
	double m = r / R;
	*x = (R+m*R)*cos(m*t) - m*R*cos(t+m*t) + 0.5;
	*y = (R+m*R)*sin(m*t) - m*R*sin(t+m*t) + 0.5;
}
