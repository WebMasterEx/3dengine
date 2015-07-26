#include "material.h"

CMaterial::CMaterial() {
	m_Device = NULL;
}

CMaterial::~CMaterial() {

}

HRESULT CMaterial::Initialize(IDirect3DDevice9* device) {
	m_Device = device;

	ZeroMemory(&m_Material, sizeof(D3DMATERIAL9));

	return S_OK;
}

void CMaterial::Shutdown() {

}

void CMaterial::setAmbientColor(float r, float g, float b, float a) {
	m_Material.Ambient.a = a;
	m_Material.Ambient.r = r;
	m_Material.Ambient.g = g;
	m_Material.Ambient.b = b;
}

//void CMaterial::setAmbientColor(COLOR4 color) {
	//m_Material.Ambient.a = color.a;
	//m_Material.Ambient.r = color.r;
	//m_Material.Ambient.g = color.g;
	//m_Material.Ambient.b = color.b;
//}

void CMaterial::setDiffuseColor(float r, float g, float b, float a) {
	m_Material.Diffuse.a = a;
	m_Material.Diffuse.r = r;
	m_Material.Diffuse.g = g;
	m_Material.Diffuse.b = b;
}

//void CMaterial::setDiffuseColor(COLOR4 color) {
	//m_Material.Diffuse.a = color.a;
	//m_Material.Diffuse.r = color.r;
	//m_Material.Diffuse.g = color.g;
	//m_Material.Diffuse.b = color.b;
//}

void CMaterial::Enable() {
	m_Device->SetMaterial(&m_Material);
}

void CMaterial::Disable() {
	//m_Device->SetMaterial(NULL);
}