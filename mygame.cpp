#include "mygame.h"

ID3DXMesh* mesh;

bool CGame::Init() {
	CBaseGame::Init();

	models["Test"] = m_ResourceManager->loadModelCube(5, 5, 5);
	models["Test"]->setPosition(-5, -5, 5);

	CMaterial* material = new CMaterial();
	material->Initialize(m_Render->getDevice());
	material->setDiffuseColor(1, 1, 1, 1);
	material->setAmbientColor(1, 1, 1, 1);

	models["Test"]->setMaterial(material);
	models["Test"]->enableLight(true);

	models["Test2"] = m_ResourceManager->loadModelTeapot();
	models["Test2"]->setPosition(-5, -5, 0);
	models["Test2"]->setMaterial(material);

	D3DXCreateTeapot(m_Render->getDevice(), &mesh, NULL);

	//light = new CLight();
	//light->Initialize(m_Render->getDevice(), LIGHT_DIRECTIONAL, 0);
	//light->setDiffuseColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	//light->setDirection(D3DXVECTOR3(0.0f, 6.0f, 0.0f));

	//light->Enable();

	m_Render->getDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_Render->getDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_Render->getDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	light = new CLight();
	light->Initialize(m_Render->getDevice(), LIGHT_POINT, 0);
	light->setDiffuseColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	light->setAmbientColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	light->setPosition(50, 50, 50);
	light->setRange(100);

	light->Set();
	light->Enable();

	m_Render->getDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);


	return true;
}

bool CGame::Update() {
	CBaseGame::Update();

	for (auto it = models.begin(); it != models.end(); ++it) {
		it->second->Rotate(1,1,1);
	}

	return true;
}

bool CGame::Render(float interpolation) {
	CBaseGame::Render(interpolation);

	m_Render->BeginScene(D3DCOLOR_ARGB(0, 0, 0, 0));

	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(&projection, D3DX_PI/4, 1, m_Window->getWidth()/m_Window->getHeight(), 1000.0f );
	m_Render->getDevice()->SetTransform(D3DTS_PROJECTION, &projection);

	D3DXMATRIX view;
	m_Camera->CalculateViewMatrix(&view);
	m_Render->getDevice()->SetTransform(D3DTS_VIEW, &view);

	for (auto it = models.begin(); it != models.end(); ++it) {
		it->second->Draw();
	}

	m_Render->EndScene();
	return true;
}

bool CGame::Shutdown() {
	for (auto it = models.begin(); it != models.end(); ++it) {
		it->second->Shutdown();
		delete it->second;
	}

	CBaseGame::Shutdown();
	return true;
}