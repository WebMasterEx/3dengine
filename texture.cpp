#include "texture.h"

CTexture::CTexture() {
	m_Texture = NULL;
	m_Device = NULL;
}

CTexture::~CTexture() {

}

HRESULT CTexture::Initialize(IDirect3DDevice9* device) {
	HRESULT hr = S_OK;
	m_Device = device;

	return hr;
}

HRESULT CTexture::loadFromFile(std::string filename) {
	HRESULT hr = S_OK;
	
	hr = D3DXCreateTextureFromFile(m_Device, filename.c_str(), &m_Texture);

	return hr;
}

void CTexture::Shutdown() {
	if (m_Texture) {
		m_Texture->Release();
		m_Texture = NULL;
	}
}

void CTexture::Enable() {
	m_Device->SetTexture(0, m_Texture);
}

void CTexture::Disable() {
	m_Device->SetTexture(0, NULL);
}