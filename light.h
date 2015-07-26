#pragma once

#include <Windows.h>
#include "dxu.h"

enum LIGHT_TYPE {
	LIGHT_DIRECTIONAL=0
};

class CLight {
public:
	CLight();
	~CLight();

	HRESULT Initialize(IDirect3DDevice9* device, LIGHT_TYPE type, int index);
	void Shutdown();

	void setType(LIGHT_TYPE type);

	void setDirection(D3DXVECTOR3 direction);

	void setDiffuseColor(D3DXCOLOR color);
	void setAmbientColor(D3DXCOLOR color);
	void setSpecularColor(D3DXCOLOR color);


	void Enable();
	void Disable();

protected:
	IDirect3DDevice9* m_Device;
	D3DLIGHT9 m_Light;
	LIGHT_TYPE m_Type;
	int m_Index;
};