//////////////////////////////////////////////////////////////////////////
// Simulate.h
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "NodeMgr.h"

class CSimulate
{
public:
	CSimulate(CNodeMgr* pNodeMgr);
	~CSimulate(void);

	void Simulate();

private:
	void sv_motor();
	void initialize();
	void sit(int Z);

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	CNodeMgr* m_pNodeMgr;

	int L;
	float buff_motor_value[18];
	float buff_motor_value1[18];
	int rxd[4];
	int flag, TABLE, shift, flag1, flag2, flag3;
	int motor_value[18][300];
	float motor[18];
};
