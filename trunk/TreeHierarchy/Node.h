//////////////////////////////////////////////////////////////////////////
// Node.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3d9.h>
#include <d3dx9.h>

enum COMPONENT { BACKGROUND = 0, NOTHING, BODY, HEAD,
				 ARM_SHOULDER_L, ARM_MIDDLE_L, ARM_LOW_L, ARM_SHOULDER_R, ARM_MIDDLE_R, ARM_LOW_R,
				 LEG_UP_L, LEG_UPMOTOR_L, LEG_MIDDLE_L, LEG_LOW_L, FOOT_MOTOR_L, FOOT_L,
				 LEG_UP_R, LEG_UPMOTOR_R, LEG_MIDDLE_R, LEG_LOW_R, FOOT_MOTOR_R, FOOT_R };

typedef struct _MESHCOMPONENT
{
	TCHAR str[32];
	COMPONENT objectID;
	COMPONENT parentID;
	float matTM[4][4];
} MESHCOMPONENT;

class CNode
{
public:
	CNode(LPDIRECT3DDEVICE9 pD3DDevice, MESHCOMPONENT meshComponent);
	~CNode(void);

	int GetObjectID() { return m_nObjectID; }
	int GetParentID() { return m_nParentID; }
	D3DXMATRIXA16* GetMatrixTM() { return &m_matTM; }

	D3DXMATRIXA16* Animate(D3DXMATRIXA16* pParentTM);
	virtual void Draw() {}

protected:
	COMPONENT m_nObjectID;
	COMPONENT m_nParentID;

	D3DXMATRIXA16 m_matLocal;		// 불변
	D3DXMATRIXA16 m_matAni;			// 변화
	D3DXMATRIXA16 m_matTM;			// 최종 출력 행렬, 변화

	LPDIRECT3DDEVICE9 m_pD3DDevice;
};


extern MESHCOMPONENT g_meshComponent[22];