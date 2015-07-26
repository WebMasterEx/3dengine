#pragma once

#include <Windows.h>

//Подключаем библиотеки
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

#include <d3d9.h>
#include <d3dx9.h>

class CRender {
public:
	CRender();
	~CRender();

	HRESULT Initialize(HWND hWnd, int width, int height, bool isWindowed);
	void Shutdown();

	void BeginScene(D3DCOLOR color);
	void EndScene();

	IDirect3DDevice9* getDevice();
	IDirect3D9* getD3D();
protected:
	IDirect3D9* m_d3d9;
	IDirect3DDevice9* m_Device;
	HWND m_hWnd;
};