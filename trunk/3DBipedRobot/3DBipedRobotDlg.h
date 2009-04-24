// 3DBipedRobotDlg.h : ��� ����
//

#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")


#include "NodeMgr.h"
#include "Camera.h"
#include "Simulate.h"
#include "ViewerDlg.h"
#include "Comm.h"

// C3DBipedRobotDlg ��ȭ ����
class C3DBipedRobotDlg : public CDialog
{
// �����Դϴ�.
public:
	C3DBipedRobotDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MY3DBIPEDROBOT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

private:
	// MFC + DirectX
	CRect					m_rtClient;		// ������
	IDirect3D9*				m_pD3D;			// ����̽�
	IDirect3DDevice9*		m_pD3DDevice;
	D3DPRESENT_PARAMETERS	m_d3dpp;		// ���÷��� ���
	bool					m_bReady;		// Rendering �غ���� üũ

public:
	void Render();							// Render �Լ�

private:
	// 3DBipedRobot
	CCamera*   m_pCamera;
	CSimulate* m_pSimul;

public:
	CNodeMgr*  m_pNodeMgr;

private:
	LPDIRECT3DVERTEXBUFFER9 m_pXYZVB;

	struct CUSTOMVERTEXXYZ
	{
		D3DXVECTOR3 position;
		D3DXCOLOR color;
	};

public:			// Simulation zMP ������!!!!!!
	CViewerDlg* m_pViewerDlg;

private:
	void InitGeometry();
	void InitObject();
	void InitMatrix();
	void InitLights();
	void DeleteObject();
	void Cleanup();

public:
	void Simulation();

	// Serial Comm
private:
	CComm m_pComm;

	int m_nSettingPort;
	int m_nSettingParity;
	int m_nSettingBaud;
	int m_nSettingData;
	int m_nSettingStop;
	int m_nSettingFlow;

	void InitSerialComm();
	TTYSTRUCT Int2TTY();

public:
	void OnBnClickedCheckConnect();		// ViewerDlg ���� Connect ������ ȣ���
	void SendData();

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();	
protected:
	virtual void OnOK();
};

DWORD WINAPI CallBackSimulation(LPVOID pVoid);