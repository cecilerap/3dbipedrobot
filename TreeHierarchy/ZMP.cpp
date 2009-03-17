//////////////////////////////////////////////////////////////////////////
// ZMP.cpp
//////////////////////////////////////////////////////////////////////////

#include "ZMP.h"

CZMP::CZMP(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
}

CZMP::~CZMP(void)
{
}

void CZMP::Check()
{
	D3DXMATRIXA16* leftFoot = m_Nodes[FOOT_L]->GetMatrixTM();

//	if(leftFoot->m[3][1] == 0 )
}