#pragma once

#include <map>
#include <string>
#include <tinyxml.h>

#include "dxu.h"
#include "texture.h"
#include "model.h"
#include "font.h"
#include "material.h"

class CResourceManager {
public:
	CResourceManager();
	~CResourceManager();

	HRESULT Initialize(IDirect3DDevice9* device);
	void Shutdown();

	CTexture* loadTexture(std::string filename);

	Model* loadModel(std::string filename);
	Model* loadModelCube(float x, float y, float z);
	Model* loadModelTeapot();
	Model* getModelByName(std::string name);

	CMaterial* loadMaterialFromFile(std::string filename);
	CMaterial* loadMaterialFromXmlNode(TiXmlElement* node);
	CMaterial* getMaterialByName(std::string name);

	Model* loadModelFromXml(std::string filename);
	Model* loadModelFromXmlNode(TiXmlElement* node);

	//void loadSceneFromFile(std::string filename);

	//CFont* loadFont();

	CTexture* getTextureByName(std::string name);

protected:
	IDirect3DDevice9* m_Device;
	std::map<std::string, Model*> m_ModelCache;
	std::map<std::string, CTexture*> m_TextureCache;
	std::map<std::string, CMaterial*> m_MaterialCache;
};