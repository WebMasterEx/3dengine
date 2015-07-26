#include "model.h"

Model::Model() {
	texture = NULL;
	m_Material = NULL;
	m_EnableLight = false;
}

Model::~Model() {

}

void Model::SetDirect3DDevice(IDirect3DDevice9* device) {
	m_Device = device;
}

void Model::Initialize() {

}

void Model::Shutdown() {
	if (texture) texture->Shutdown();
	if (m_Material) m_Material->Shutdown();
}

void Model::Draw() {

}

void Model::enableLight(bool enable) {
	m_EnableLight = enable;
	if (enable) {
		//D3DXComputeNormals(mesh, NULL);
	}
}

void Model::SetMatrix() {
	D3DXMATRIX translate;
	D3DXMATRIX scale;
	D3DXMATRIX rotate;
	D3DXMATRIX world;


	IMovable::getMatrix(&translate);
	IScalable::getMatrix(&scale);
	IRotatable::getMatrix(&rotate);

	world = rotate * scale * translate;

	m_Device->SetTransform(D3DTS_WORLD, &world);
}

HRESULT Model::loadFromFile(std::string filename) {
	return S_OK;
}


void Model::setTexture(std::string filename) {
	texture = new CTexture();
	texture->Initialize(m_Device);
	texture->loadFromFile(filename);
}

void Model::setMaterial(CMaterial* material) {
	m_Material = material;
}

void Model::beforeDraw() {
	SetMatrix();
	if (texture) texture->Enable();
	if (m_Material) m_Material->Enable();
	m_Device->SetRenderState(D3DRS_LIGHTING, true);
}

void Model::afterDraw() {
	if (texture) texture->Disable();
	if (m_Material) m_Material->Disable();
}


void ModelCube::Initialize(float x, float y, float z) {
	D3DXCreateBox(m_Device, x, y, z, &mesh, NULL);
}

void ModelCube::Shutdown() {
	mesh->Release();
	Model::Shutdown();
}

void ModelCube::Draw() {
	beforeDraw();
	mesh->DrawSubset(0);
	afterDraw();
}

void ModelTeapot::Initialize() {
	D3DXCreateTeapot(m_Device, &mesh, NULL);
}

void ModelTeapot::Shutdown() {
	mesh->Release();
	Model::Shutdown();
}

void ModelTeapot::Draw() {
	beforeDraw();
	mesh->DrawSubset(0);
	afterDraw();
}

void ModelX::Initialize() {
	//D3DXCreateTeapot(m_Device, &mesh, NULL);
}

void ModelX::Shutdown() {
	mesh->Release();
	Model::Shutdown();
}

void ModelX::Draw() {
	beforeDraw();
	mesh->DrawSubset(0);
	afterDraw();
}

HRESULT ModelX::loadFromFile(std::string filename) {
	D3DXLoadMeshFromX(filename.c_str(),0,m_Device,NULL,NULL,NULL,NULL,&mesh);

	return S_OK;
}