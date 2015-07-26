#pragma once

#include <Windows.h>
#include "cwindow.h"
#include "cinputmanager.h"
#include "crender.h"
#include "light.h"
#include "resourcemanager.h"
#include "log.h"

enum CSystemEvent {
	EVENT_INIT, EVENT_SHUTDOWN, EVENT_UPDATE, EVENT_RENDER
};

typedef bool (*SystemEventHandler)();

class CSystem {
public:
	CSystem();
	~CSystem();

	HRESULT Initialize(CWindow* window);
	void Shutdown();

	void Run();
	bool Update();
	bool Render();

	float getInterpolation();

	void setCallback(CSystemEvent type, SystemEventHandler callback);

	CWindow* getWindow();
	CInputManager* getInputManager();
	CRender* getRender();
	CResourceManager* getResourceManager();
protected:
	int m_UpdatesPerSecond;
	float m_Interpolation;

	CWindow* m_Window;
	CInputManager* m_InputManager;
	CRender* m_Render;
	CResourceManager* m_ResourceManager;

	SystemEventHandler initCallback;
	SystemEventHandler updateCallback;
	SystemEventHandler shutdownCallback;
	SystemEventHandler renderCallback;
};