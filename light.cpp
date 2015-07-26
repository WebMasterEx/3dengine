#include "light.h"

CLight::CLight() {

}

CLight::~CLight() {

}

HRESULT CLight::Initialize(IDirect3DDevice9* device, LIGHT_TYPE type, int index) {
	HRESULT hr = S_OK;

	m_Device = device;
	m_Index = index;

	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));

	//m_Light.Range = 1000.0;
	setType(type);
	
	return hr;
}

void CLight::setType(LIGHT_TYPE type) {
	switch (type) {
		case LIGHT_DIRECTIONAL:
			m_Light.Type = D3DLIGHT_DIRECTIONAL;
		break;

		case LIGHT_POINT:
			m_Light.Type = D3DLIGHT_POINT;
		break;
	}

	m_Type = type;
}

void CLight::Shutdown() {

}

void CLight::setDirection(D3DXVECTOR3 direction) {
	if (m_Type == LIGHT_DIRECTIONAL) {
		m_Light.Direction = direction;
	}
}

void CLight::setAmbientColor(D3DXCOLOR color) {
	m_Light.Ambient = color;
}

void CLight::setDiffuseColor(D3DXCOLOR color) {
	m_Light.Diffuse = color;
}

void CLight::setSpecularColor(D3DXCOLOR color) {
	m_Light.Specular = color;
}

void CLight::Enable() {
	
	m_Device->LightEnable(m_Index, TRUE);
}

void CLight::Set() {
	m_Device->SetLight(m_Index, &m_Light);
}

void CLight::Disable() {
	m_Device->LightEnable(m_Index, FALSE);
}

void CLight::setAttenuation(float a0, float a1, float a2) {
	m_Light.Attenuation0 = a0;
	m_Light.Attenuation1 = a1;
	m_Light.Attenuation2 = a2;
}

void CLight::setRange(float range) {
	m_Light.Range = range;
}

void CLight::setPosition(float x, float y, float z) {
	m_Light.Position = D3DXVECTOR3(x, y, z);
}