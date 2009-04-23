// NodeMgr.h : 헤더 파일
//

#pragma once
#include <vector>
using namespace std;

#include "Node.h"
#include "Mesh.h"
#include "ZMP.h"

class CNodeMgr
{
public:
	CNodeMgr(LPDIRECT3DDEVICE9 pD3DDevice);
	~CNodeMgr(void);

	void Animate();
	void Draw();
	void SetWeight();

	void SetAngle(COMPONENT id, float angle);
	CNode* GetNodes(COMPONENT id) { return m_nodes[id]; }
	D3DXVECTOR3 GetCenterWeight() { return m_vCtWeight; }
	D3DXVECTOR3 GetOldCenterWeight() { return m_vOldCtWeight; }

protected:
	vector<CNode*> m_nodes;

	LPDIRECT3DDEVICE9 m_pD3DDevice;
	D3DXMATRIXA16 m_matTM;

	D3DXVECTOR3 m_vOldCtWeight, m_vCtWeight;

public:
	CZMP* m_pLeftZMP, * m_pRightZMP;
};
