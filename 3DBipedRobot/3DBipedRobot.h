// 3DBipedRobot.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// C3DBipedRobotApp:
// �� Ŭ������ ������ ���ؼ��� 3DBipedRobot.cpp�� �����Ͻʽÿ�.
//

class C3DBipedRobotApp : public CWinApp
{
public:
	C3DBipedRobotApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern C3DBipedRobotApp theApp;