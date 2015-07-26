#include "crender.h"
#include "log.h"

CRender::CRender() {
	m_d3d9 = NULL;
	m_Device = NULL;
}

CRender::~CRender() {

}

HRESULT CRender::Initialize(HWND hWnd, int width, int height, bool isWindowed) {
	Log::Write("Initialize Render!");

	HRESULT hr = S_OK;
	m_hWnd = hWnd;

	m_d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DDISPLAYMODE DisplayMode;
	m_d3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisplayMode);

	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp, sizeof(pp));

	pp.BackBufferWidth = width;
	pp.BackBufferHeight = height;
	pp.BackBufferFormat = D3DFMT_X8R8G8B8;
	pp.BackBufferCount = 1;
	pp.MultiSampleType = D3DMULTISAMPLE_NONE;
	pp.MultiSampleQuality = 0;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.hDeviceWindow = hWnd;
	pp.Windowed = isWindowed;
	pp.EnableAutoDepthStencil = true;
	pp.AutoDepthStencilFormat = D3DFMT_D16;
	pp.Flags = 0;
	pp.FullScreen_RefreshRateInHz = 0;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	hr = m_d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &m_Device);

	if (FAILED(hr)) {
		return hr;
	}

	m_Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	m_Device->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_Device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	return hr;
}

void CRender::Shutdown() {
	if (m_Device) {
		m_Device->Release();
		m_Device = NULL;
	}

	if (m_d3d9) {
		m_d3d9->Release();
		m_d3d9 = NULL;
	}
}

void CRender::BeginScene(D3DCOLOR color) {
	m_Device->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, color, 1.0, 0);
	m_Device->BeginScene();
}

void CRender::EndScene() {
	m_Device->EndScene();
	m_Device->Present(NULL, NULL, NULL, NULL);
}

IDirect3DDevice9* CRender::getDevice() {


	return m_Device;
}

IDirect3D9* CRender::getD3D() {
	return m_d3d9;
}