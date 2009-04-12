//////////////////////////////////////////////////////////////////////////
// ForceSensor.cpp
//////////////////////////////////////////////////////////////////////////

#include "ForceSensor.h"

CForceSensor::CForceSensor(LPDIRECT3DDEVICE9 pD3DDevice, D3DXVECTOR3 vec)
{
	m_pD3DDevice = pD3DDevice;
	m_vec = vec;

	memset(m_Vertics, 0, sizeof(m_Vertics));

	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(m_Vertics), 0, D3DFVF_XYZ|D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &m_pVB, NULL)))
		return;
}

CForceSensor::~CForceSensor(void)
{
}

void CForceSensor::Draw()
{
	m_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEXFOOT));
	m_pD3DDevice->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
	m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 4);
}

void CForceSensor::SetVertex(D3DXMATRIXA16* pMatTM)
{
	D3DXMATRIXA16 matTM;
	D3DXMatrixIdentity(&matTM);
	matTM.m[3][0] = m_vec.x;
	matTM.m[3][1] = m_vec.y;
	matTM.m[3][2] = m_vec.z;

	matTM *= (*pMatTM);

	m_Vertics[0].position.x = matTM.m[3][0];
	m_Vertics[0].position.y = matTM.m[3][1];
	m_Vertics[0].position.z = 0;				// Z축으로는 발과 딱 붙여서 이동하면 되므로 계산하지 않아도 됨

	m_Vertics[1].position.x = matTM.m[3][0] +3;
	m_Vertics[1].position.y = matTM.m[3][1];
	m_Vertics[1].position.z = 0;

	m_Vertics[2].position.x = matTM.m[3][0] +3;
	m_Vertics[2].position.y = matTM.m[3][1] +3;
	m_Vertics[2].position.z = 0;

	m_Vertics[3].position.x = matTM.m[3][0];
	m_Vertics[3].position.y = matTM.m[3][1] +3;
	m_Vertics[3].position.z = 0;

	m_Vertics[4].position.x = matTM.m[3][0];
	m_Vertics[4].position.y = matTM.m[3][1];
	m_Vertics[4].position.z = 0;

	for(int j = 0; j < 5; ++j)
		m_Vertics[j].color = D3DXCOLOR(0x0066ff);

	VOID* pVertices;
	if(FAILED(m_pVB->Lock(0, sizeof(m_Vertics), (void**)&pVertices, 0)))
		return;
	memcpy(pVertices, m_Vertics, sizeof(m_Vertics));
	m_pVB->Unlock();
}