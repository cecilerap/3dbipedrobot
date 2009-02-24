//////////////////////////////////////////////////////////////////////////
// DirectX3D.h
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// DirectX3D.h
//////////////////////////////////////////////////////////////////////////

#pragma once

class CDirectX3D
{
public:
	CDirectX3D(void);
	~CDirectX3D(void);

	HRESULT InitD3D(HWND hWnd);
	HRESULT InitGeometry();
	void Cleanup();

	void Render();

	void SetupLights();
	void SetupMatrices();

private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
};
