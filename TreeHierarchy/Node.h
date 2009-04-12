//////////////////////////////////////////////////////////////////////////
// Node.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3d9.h>
#include <d3dx9.h>

enum COMPONENT { NOTHING = 0, BODY, HEAD,
				 ARM_SHOULDER_L, ARM_MIDDLE_L, ARM_LOW_L, ARM_SHOULDER_R, ARM_MIDDLE_R, ARM_LOW_R,
				 LEG_UP_L, LEG_UPMOTOR_L, LEG_MIDDLE_L, LEG_LOW_L, FOOT_L, FOOT_MOTOR_L,
				 LEG_UP_R, LEG_UPMOTOR_R, LEG_MIDDLE_R, LEG_LOW_R, FOOT_R, FOOT_MOTOR_R/*, ORIGIN*/ };

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

	D3DXMATRIXA16* GetMatrixLocal() { return &m_matLocal; }
	D3DXMATRIXA16* GetMatrixAni() { return &m_matAni; }
	D3DXMATRIXA16* GetMatrixTM() { return &m_matTM; }

	D3DXMATRIXA16* Animate(D3DXMATRIXA16* pParentTM);
	virtual void Draw() {}

	void SetAngle(D3DXMATRIX* (__stdcall *pfunc)(D3DXMATRIX*, FLOAT), float angle);
	void SetPosition(float x, float y, float z);

protected:
	COMPONENT m_nObjectID;
	COMPONENT m_nParentID;

	D3DXMATRIXA16 m_matLocal;		// 불변
	D3DXMATRIXA16 m_matAni;			// 변화
	D3DXMATRIXA16 m_matTM;			// 최종 출력 행렬, 변화

	LPDIRECT3DDEVICE9 m_pD3DDevice;

	float m_angle;
};


extern MESHCOMPONENT g_meshComponent[22];