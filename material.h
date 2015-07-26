#pragma once

#include <d3d9.h>
#include <Windows.h>

class CMaterial {
public:
	CMaterial();
	~CMaterial();

	HRESULT Initialize(IDirect3DDevice9* device);
	void Shutdown();

	void setDiffuseColor(float r, float g=0, float b=0, float a=0);
	//void setDiffuseColor(COLOR4 color);

	void setAmbientColor(float r, float g=0, float b=0, float a=0);
	//void setAmbientColor(COLOR4 color);

	void Enable();
	void Disable();

protected:
	D3DMATERIAL9 m_Material;
	IDirect3DDevice9* m_Device;
	//D3DMATERIAL9 mat;
};