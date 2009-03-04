//////////////////////////////////////////////////////////////////////////
// TreeHierarchy.cpp
//////////////////////////////////////////////////////////////////////////

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "DirectX3D.h"

CDirectX3D g_DirectX3D;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_LBUTTONUP:
		g_DirectX3D.FrameMove(UP, LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_LBUTTONDOWN:
		g_DirectX3D.FrameMove(DOWN, LOWORD(lParam), HIWORD(lParam));
		break;


	case WM_MOUSEWHEEL:
		{
			if((int)wParam < 0)
				g_DirectX3D.FrameZoom(DOWN);
			else
				g_DirectX3D.FrameZoom(UP);
		}
		break;


	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
		SetCapture(hWnd);
		g_DirectX3D.SetMousePos(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_RBUTTONUP:
		ReleaseCapture();
		break;


	case WM_MOUSEMOVE:
		if(MK_LBUTTON & wParam)
			g_DirectX3D.FrameMove(MOVE, LOWORD(lParam), HIWORD(lParam));
		else if(MK_RBUTTON & wParam)
			g_DirectX3D.FrameRotate(LOWORD(lParam), HIWORD(lParam));
		break;
	

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wndClass = {sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL),
						   NULL, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL, L"D3D Tutorial", NULL};
	RegisterClassEx(&wndClass);

	hWnd = CreateWindow(L"D3D Tutorial", L"TreeHierarchy", WS_OVERLAPPEDWINDOW,
						100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, GetDesktopWindow(), NULL, wndClass.hInstance, NULL);
	ShowWindow(hWnd, SW_SHOWDEFAULT);

	MSG msg = {0,};
	if(SUCCEEDED(g_DirectX3D.InitD3D(hWnd)))
	{
		if(SUCCEEDED(g_DirectX3D.InitObjects()))
		{
			if(SUCCEEDED(g_DirectX3D.InitGeometry()))
			{
				UpdateWindow(hWnd);
				while(msg.message != WM_QUIT)
				{
					if(PeekMessage(&msg, NULL, 0L, 0L, PM_REMOVE))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
					else
						g_DirectX3D.Render();
				}
			}
		}
	}

	g_DirectX3D.DeleteObjects();
	UnregisterClass(L"D3D Tutorial", wndClass.hInstance);
	return 0;
}