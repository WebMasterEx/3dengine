#pragma once

#include "csystem.h"
#include "camera.h"

class CBaseGame {
public:
	CBaseGame();
	virtual ~CBaseGame();

	virtual void setEngine(CSystem* engine);

	virtual bool Init();
	virtual bool Update();
	virtual bool Render(float interpolation);
	virtual bool Shutdown();

protected:
	CCamera* m_Camera;

	CSystem* m_System;
	CRender* m_Render;
	CInputManager* m_InputManager;
	CResourceManager* m_ResourceManager;
	CWindow* m_Window;
};