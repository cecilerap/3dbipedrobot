//////////////////////////////////////////////////////////////////////////
// ZMP.cpp
//////////////////////////////////////////////////////////////////////////

#include "ZMP.h"

CZMP::CZMP(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;

	m_pos[0][0].x = -6.768f, m_pos[0][0].y = 0.017f, m_pos[0][0].z = -23.719f;
	m_pos[0][1].x = -6.774f, m_pos[0][1].y = 0.017f, m_pos[0][1].z =   3.741f;
	m_pos[0][2].x =  8.316f, m_pos[0][2].y = 0.017f, m_pos[0][2].z =   3.741f;
	m_pos[0][3].x =  8.316f, m_pos[0][3].y = 0.017f, m_pos[0][3].z = -23.716f;

	m_pos[1][0].x = -8.280f, m_pos[1][0].y = -0.027f, m_pos[1][0].z = -23.546f;
	m_pos[1][1].x = -8.312f, m_pos[1][1].y = -0.027f, m_pos[1][1].z =   4.038f;
	m_pos[1][2].x =  7.010f, m_pos[1][2].y = -0.027f, m_pos[1][2].z =   4.038f;
	m_pos[1][3].x =  7.010f, m_pos[1][3].y = -0.027f, m_pos[1][3].z = -23.811f;

	memset(m_Vertics, 0, sizeof(m_Vertics));
}

CZMP::~CZMP(void)
{
}

void CZMP::SetVertics(DIR dir, D3DXMATRIXA16* pMatTM)
{
// 	for(int i = 0; i < 4; ++i)
// 	{
// 		m_Vertics[dir][i][0].position.x = pMatTM->m[3][0] + m_pos[dir][i].x;
// 		m_Vertics[dir][i][0].position.y = pMatTM->m[3][1] + m_pos[dir][i].y;
// 		m_Vertics[dir][i][0].position.z = pMatTM->m[3][2] + m_pos[dir][i].z;
// 
// 		m_Vertics[dir][i][1].position.x = pMatTM->m[3][0] + m_pos[dir][i].x +3;
// 		m_Vertics[dir][i][1].position.y = pMatTM->m[3][1] + m_pos[dir][i].y;
// 		m_Vertics[dir][i][1].position.z = pMatTM->m[3][2] + m_pos[dir][i].z;
// 
// 		m_Vertics[dir][i][2].position.x = pMatTM->m[3][0] + m_pos[dir][i].x +3;
// 		m_Vertics[dir][i][2].position.y = pMatTM->m[3][1] + m_pos[dir][i].y;
// 		m_Vertics[dir][i][2].position.z = pMatTM->m[3][2] + m_pos[dir][i].z +3;
// 
// 		m_Vertics[dir][i][3].position.x = pMatTM->m[3][0] + m_pos[dir][i].x;
// 		m_Vertics[dir][i][3].position.y = pMatTM->m[3][1] + m_pos[dir][i].y;
// 		m_Vertics[dir][i][3].position.z = pMatTM->m[3][2] + m_pos[dir][i].z +3;
// 
// 		for(int j = 0; j < 4; ++j)
// 			m_Vertics[dir][i][j].color = D3DXCOLOR(0xff6600);
// 
// // 		m_endPos[dir][i].x = pMatTM->m[3][0] + m_pos[dir][i].x;
// // 		m_endPos[dir][i].y = pMatTM->m[3][1] + m_pos[dir][i].y;
// // 		m_endPos[dir][i].z = pMatTM->m[3][2] + m_pos[dir][i].z;
// 	}

	m_Vertics[dir][0].position.x = pMatTM->m[3][0] + m_pos[dir][0].x;
	m_Vertics[dir][0].position.y = pMatTM->m[3][1] + m_pos[dir][0].y;
	m_Vertics[dir][0].position.z = pMatTM->m[3][2] + m_pos[dir][0].z;
			 
	m_Vertics[dir][1].position.x = pMatTM->m[3][0] + m_pos[dir][0].x +3;
	m_Vertics[dir][1].position.y = pMatTM->m[3][1] + m_pos[dir][0].y;
	m_Vertics[dir][1].position.z = pMatTM->m[3][2] + m_pos[dir][0].z;
			 
	m_Vertics[dir][2].position.x = pMatTM->m[3][0] + m_pos[dir][0].x +3;
	m_Vertics[dir][2].position.y = pMatTM->m[3][1] + m_pos[dir][0].y +3;
	m_Vertics[dir][2].position.z = pMatTM->m[3][2] + m_pos[dir][0].z;
			 
	m_Vertics[dir][3].position.x = pMatTM->m[3][0] + m_pos[dir][0].x;
	m_Vertics[dir][3].position.y = pMatTM->m[3][1] + m_pos[dir][0].y +3;
	m_Vertics[dir][3].position.z = pMatTM->m[3][2] + m_pos[dir][0].z;
			 
	m_Vertics[dir][4].position.x = pMatTM->m[3][0] + m_pos[dir][0].x;
	m_Vertics[dir][4].position.y = pMatTM->m[3][1] + m_pos[dir][0].y;
	m_Vertics[dir][4].position.z = pMatTM->m[3][2] + m_pos[dir][0].z;

	for(int j = 0; j < 5; ++j)
		m_Vertics[dir][j].color = D3DXCOLOR(0xff6600);
}

void CZMP::Initialize()
{
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(m_Vertics), 0, D3DFVF_XYZ|D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &m_pVB, NULL)))
		return;

	VOID* pVertices;
	if(FAILED(m_pVB->Lock(0, sizeof(m_Vertics), (void**)&pVertices, 0)))
		return;
	memcpy(pVertices, m_Vertics, sizeof(m_Vertics));
	m_pVB->Unlock();
}

void CZMP::Draw()
{
	m_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEXFOOT));
	m_pD3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 8);
}

//void CZMP::Check(CNode* pNode)
//{
// 	D3DXMATRIXA16* originTM = pNode->GetMatrixTM();
// 	D3DXMATRIXA16 local[4], TM[4];
// 
// 	for(int i = 0; i < 4; ++i)
// 	{
// 		local[i] = pNode->GetMatrixLocal();
// 
// 		local[i].m[3][0] += m_posLeft[i][0];
// 		local[i].m[3][1] += m_posLeft[i][1];
// 		local[i].m[3][2] += m_posLeft[i][2];
// 
// 		TM[i] = *originTM * local[i];
//
//		if(TM[i].m[3][1] < 0)
// 
// 	}
//}