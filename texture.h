#pragma once

#include <string>

#include <Windows.h>
#include "dxu.h"

class CTexture {
public:
	CTexture();
	~CTexture();

	HRESULT Initialize(IDirect3DDevice9* device);
	void Shutdown();

	HRESULT loadFromFile(std::string filename);

	void Enable();
	void Disable();

protected:
	IDirect3DTexture9* m_Texture;
	IDirect3DDevice9* m_Device;
};