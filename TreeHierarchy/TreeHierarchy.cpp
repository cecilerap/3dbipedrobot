//////////////////////////////////////////////////////////////////////////
// TreeHierarchy.cpp
//////////////////////////////////////////////////////////////////////////

#include <WindowsX.h>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "ws2_32.lib")

#include "DirectX3D.h"
#include "Simulate.h"
#include "ServerSocket.h"

#define PORTNUM		51000

CDirectX3D g_DirectX3D;
CSimulate  g_Simul;
CServerSocket g_Sock;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnDestroy(HWND hwnd);
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
void OnMouseWheel(HWND hwnd, int xPos, int yPos, int zDelta, UINT fwKeys);
void OnChar(HWND hwnd, TCHAR ch, int cRepeat);
DWORD CALLBACK ServerProc(void* pVoid);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	WSADATA wd;
	WSAStartup( MAKEWORD(2,2), &wd );

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

	WSACleanup();
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch(iMessage)
	{
		HANDLE_MSG(hWnd, WM_CREATE,        OnCreate);
		HANDLE_MSG(hWnd, WM_DESTROY,       OnDestroy);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN,   OnLButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONDBLCLK, OnLButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONUP,     OnLButtonUp);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE,     OnMouseMove);
		HANDLE_MSG(hWnd, WM_MOUSEWHEEL,    OnMouseWheel);
		HANDLE_MSG(hWnd, WM_CHAR,          OnChar);
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	CloseHandle(CreateThread(NULL, 0, ServerProc, hwnd, 0, NULL));
	return TRUE;
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage( 0 );
}

void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	SetCapture(hwnd);
	g_DirectX3D.m_pCamera->SetMousePos(x, y);
}

void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	ReleaseCapture();
}

void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	RECT rt;
	GetClientRect(hwnd, &rt);
	
	POINT pt;
	pt.x = x, pt.y = y;
	
	if(!PtInRect(&rt, pt))
		return;

	if(MK_LBUTTON & keyFlags)
		g_DirectX3D.m_pCamera->Move(x, y);
}

void OnMouseWheel(HWND hwnd, int xPos, int yPos, int zDelta, UINT fwKeys)
{
	g_DirectX3D.m_pCamera->Zoom(zDelta);
}

void OnChar(HWND hwnd, TCHAR ch, int cRepeat)
{
	switch(ch)
	{
	case 'W' :
	case 'w' : g_Simul.SetState(CSimulate::WALK);
		break;

	case 'R' :
	case 'r' : g_Simul.SetState(CSimulate::READY);
		break;

	case 'S':
	case 's':
		if(g_Sock.m_sock != INVALID_SOCKET)	
			g_Sock.Send("hello", 5);
		break;
	}
}

DWORD CALLBACK ServerProc(void* pVoid)
{
	HWND hWnd = (HWND)pVoid;

	if(!g_Sock.Create(PORTNUM))
		return FALSE;

	SOCKET client = g_Sock.Accept();
	if(client == INVALID_SOCKET)
		return FALSE;

 	return TRUE;
}