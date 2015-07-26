#pragma once

#include <string>
#include <Windows.h>

#include "dxu.h"
#include "transformations.h"
#include "texture.h"
#include "material.h"

class Model : public IMovable, public IScalable, public IRotatable {
public:
	Model();
	~Model();

	void SetDirect3DDevice(IDirect3DDevice9* device);
	virtual void Initialize();
	virtual void Shutdown();

	virtual HRESULT loadFromFile(std::string filename);

	virtual void Draw();

	virtual void setTexture(std::string filename);
	virtual void beforeDraw();
	virtual void afterDraw();

	virtual void setMaterial(CMaterial* material);

	virtual void enableLight(bool enable);

protected:
	virtual void SetMatrix();
	IDirect3DDevice9* m_Device;
	CTexture* texture;
	CMaterial* m_Material;
	ID3DXMesh* mesh;

	bool m_EnableLight;
};

class ModelCube : public Model {
public:
	virtual void Initialize(float x, float y, float z);
	virtual void Shutdown();

	virtual void Draw();
protected:

};

class ModelTeapot : public Model {
public:
	virtual void Initialize();
	virtual void Shutdown();

	virtual void Draw();
protected:
};

class ModelX : public Model {
public:
	virtual HRESULT loadFromFile(std::string filename);

	virtual void Initialize();
	virtual void Shutdown();

	virtual void Draw();
protected:
};