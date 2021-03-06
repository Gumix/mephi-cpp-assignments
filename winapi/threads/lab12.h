#pragma once

#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL OnCreate(HWND, LPCREATESTRUCT);
void OnCommand(HWND, int, HWND, UINT);
void OnDestroy(HWND);

DWORD WINAPI Thread1(LPVOID);
DWORD WINAPI Thread2(LPVOID);
DWORD WINAPI Thread3(LPVOID);
DWORD WINAPI Thread4(LPVOID);