//////////////////////////////////////////////////////////////////////////
// TreeHierarchy.cpp
//////////////////////////////////////////////////////////////////////////

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "DirectX3D.h"
#include "Simulate.h"

CDirectX3D g_DirectX3D;
CSimulate  g_Simul;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch(iMessage)
	{
	case WM_LBUTTONDOWN:
		SetCapture(hWnd);
		g_DirectX3D.m_pCamera->SetMousePos(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_LBUTTONUP:
		ReleaseCapture();
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
		SetCapture(hWnd);
		g_DirectX3D.m_pCamera->SetMousePos(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_RBUTTONUP:
		ReleaseCapture();
		break;

	case WM_MOUSEMOVE:
		{
			RECT rt;
			GetClientRect(hWnd, &rt);
			POINT pt;
			pt.x = LOWORD(lParam), pt.y = HIWORD(lParam);
			if(!PtInRect(&rt, pt))
				break;
			if(MK_LBUTTON & wParam)
				g_DirectX3D.m_pCamera->Move(LOWORD(lParam), HIWORD(lParam));
		}		
		break;

	case WM_MOUSEWHEEL:
		g_DirectX3D.m_pCamera->Zoom((int)wParam);
		break;

	case WM_CHAR:
		switch((TCHAR)wParam)
		{
		case 'W' :
		case 'w' : g_Simul.SetState(CSimulate::WALK);
			break;

		case 'R' :
		case 'r' : g_Simul.SetState(CSimulate::READY);
			break;
		}
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
				g_Simul.SetDirectX3D(&g_DirectX3D);
				g_Simul.SetNodeMgr(g_DirectX3D.GetNodeMgr());

				UpdateWindow(hWnd);
				while(msg.message != WM_QUIT)
				{
					if(PeekMessage(&msg, NULL, 0L, 0L, PM_REMOVE))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
					else
						g_Simul.Simulate();
				}
			}
		}
	}

	g_DirectX3D.DeleteObjects();
	UnregisterClass(L"D3D Tutorial", wndClass.hInstance);
	return 0;
}