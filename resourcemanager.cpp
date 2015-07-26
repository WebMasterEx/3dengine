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
   for (auto it = m_ModelCache.begin(); it != m_ModelCache.end(); ++it) {
	   delete it->second;
   }

   for (auto it = m_MaterialCache.begin(); it != m_MaterialCache.end(); ++it) {
	   delete it->second;
   }

   for (auto it = m_TextureCache.begin(); it != m_TextureCache.end(); ++it) {
	   delete it->second;
   }
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

CTexture* CResourceManager::getTextureByName(std::string name) {
	return m_TextureCache.find(name)->second;
}

CMaterial* CResourceManager::getMaterialByName(std::string name) {
	return m_MaterialCache.find(name)->second;
}

Model* CResourceManager::getModelByName(std::string name) {
	return m_ModelCache.find(name)->second;
}

CMaterial* CResourceManager::loadMaterialFromFile(std::string filename) {
	TiXmlDocument *xml_file = new TiXmlDocument(filename.c_str());
	if(!xml_file->LoadFile()) return NULL; 

	TiXmlElement *material_xml = xml_file->FirstChildElement("material"); 

	CMaterial* material = loadMaterialFromXmlNode(material_xml);
	delete xml_file;
	return material;
}

CMaterial* CResourceManager::loadMaterialFromXmlNode(TiXmlElement* node) {
	TiXmlElement *diffuse = node->FirstChildElement("diffuse"); 
	TiXmlElement *ambient = node->FirstChildElement("ambient"); 

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

Model* CResourceManager::loadModelFromXml(std::string filename) {
	TiXmlDocument *xml_file = new TiXmlDocument(filename.c_str());
	if(!xml_file->LoadFile()) return NULL; 

	TiXmlElement *material_xml = xml_file->FirstChildElement("model"); 
	
	Model* model = loadModelFromXmlNode(material_xml);
	delete xml_file;
	return model;
} 

Model* CResourceManager::loadModelFromXmlNode(TiXmlElement* node) {
	std::string name = node->Attribute("name");
	std::string type = node->FirstChildElement("type")->Value();

	Model* model;

	if (type == "default") {
		std::string default_type = node->FirstChildElement("default_type")->Value();
		if (default_type == "teapot") model = this->loadModelTeapot();
		else if (default_type == "cube") model = this->loadModelCube(5, 5, 5);
	}
	else if (type == "custom") {
		std::string custom_type = node->FirstChildElement("custom_type")->Value();
		std::string file = node->FirstChildElement("file")->Value();

		if (custom_type == "x") model = this->loadModel(file);
	}

	int textureEnable;
	TiXmlElement* texture = node->FirstChildElement("texture");
	texture->Attribute("active", &textureEnable);

	if (textureEnable == 1) {
		//model->setTexture("tiger.bmp");
	}

	double x,y,z;
	TiXmlElement* position = node->FirstChildElement("position");
	position->Attribute("x", &x);
	position->Attribute("y", &y);
	position->Attribute("z", &z);

	model->setPosition(x, y, z);

	TiXmlElement* material_xml = node->FirstChildElement("material");
	CMaterial* material = this->loadMaterialFromXmlNode(material_xml);

	std::string material_name = name + "_" + material_xml->Attribute("name");
	m_MaterialCache[material_name] = material;

	model->setMaterial(material);

	m_ModelCache[name] = model;

	return model;
}