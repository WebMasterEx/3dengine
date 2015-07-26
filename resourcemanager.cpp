#include "resourcemanager.h"

CResourceManager::CResourceManager() {
	m_Device = NULL;
}

CResourceManager::~CResourceManager() {

}

HRESULT CResourceManager::Initialize(IDirect3DDevice9* device) {
	m_Device = device;

	return S_OK;
}

void CResourceManager::Shutdown() {

}

Model* CResourceManager::loadModel(std::string filename) {
	ModelX* model = new ModelX();
	model->SetDirect3DDevice(m_Device);
	model->loadFromFile(filename);
	model->Initialize();

	return model;
}

Model* CResourceManager::loadModelCube(float x, float y, float z) {
	ModelCube* cube = new ModelCube();
	cube->SetDirect3DDevice(m_Device);
	cube->Initialize(x, y, z);

	return (Model*)cube;
}

Model* CResourceManager::loadModelTeapot() {
	ModelTeapot* teapot = new ModelTeapot();


	teapot->SetDirect3DDevice(m_Device);
	teapot->Initialize();

	return (Model*)teapot;
}

//CFont* ResourceManager::loadFont() {
	//CFont* font = new CFont();
	//font->Initialize(m_Device);
	//return font;
//}

CTexture* CResourceManager::loadTexture(std::string filename) {
	CTexture* texture = new CTexture();
	texture->Initialize(m_Device);
	texture->loadFromFile(filename);
	return texture;
}

CMaterial* CResourceManager::loadMaterialFromFile(std::string filename) {
	TiXmlDocument *xml_file = new TiXmlDocument(filename.c_str());
	if(!xml_file->LoadFile()) return NULL; 

	TiXmlElement *material_xml = xml_file->FirstChildElement("material"); 
	TiXmlElement *diffuse = material_xml->FirstChildElement("diffuse"); 
	TiXmlElement *ambient = material_xml->FirstChildElement("ambient"); 

	CMaterial* material = new CMaterial();
	material->Initialize(m_Device);

	double r,b,g,a;
	diffuse->Attribute("r", &r);
	diffuse->Attribute("g", &g);
	diffuse->Attribute("b", &b);
	diffuse->Attribute("a", &a);

	material->setDiffuseColor(r, g, b, a);

	ambient->Attribute("r", &r);
	ambient->Attribute("g", &g);
	ambient->Attribute("b", &b);
	ambient->Attribute("a", &a);
	
	material->setAmbientColor(r,g,b,a);

	return material;
}