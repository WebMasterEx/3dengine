#include "csystem.h"

CSystem::CSystem() {
	m_Window = NULL;
	m_InputManager = NULL;
	m_Render = NULL;
	m_ResourceManager = NULL;

	m_UpdatesPerSecond = 35;
	m_Interpolation = 0;
}

CSystem::~CSystem() {

}

HRESULT CSystem::Initialize(CWindow* window) {
	Log::Initialize("log.txt");
	Log::Write("Start system initialize!");

	HRESULT hr = S_OK;
	m_Window = window;
	m_InputManager = new CInputManager();

	hr = m_InputManager->Initialize(window->getHandle());
	if (FAILED(hr)) {
		return hr;
	}

	m_Render = new CRender();
	hr = m_Render->Initialize(window->getHandle(), window->getWidth(), window->getHeight(), window->isWindowed());
	if (FAILED(hr)) {
		return hr;
	}

	m_ResourceManager = new CResourceManager();
	hr = m_ResourceManager->Initialize(m_Render->getDevice());
	if (FAILED(hr)) {
		return hr;
	}

	Log::Write("Initialize callback!");
	initCallback();

	Log::Write("Initialize done!");

	return hr;
}

void CSystem::Shutdown() {
	shutdownCallback();

	if (m_InputManager) {
		m_InputManager->Shutdown();
		delete m_InputManager;
		m_InputManager = NULL;
	}

	if (m_ResourceManager) {
		m_ResourceManager->Shutdown();
		delete m_ResourceManager;
		m_ResourceManager = NULL;
	}

	if (m_Render) {
		m_Render->Shutdown();
		delete m_Render;
		m_Render = NULL;
	}

	if (m_Window) {
		m_Window->Shutdown();
		delete m_Window;
		m_Window = NULL;
	}
}

void CSystem::Run() {
	MSG msg;
	bool done = false;
	bool result = true;

	ZeroMemory(&msg, sizeof(MSG));

    const int SKIP_TICKS = 1000 / m_UpdatesPerSecond;
    const int MAX_FRAMESKIP = 5;

    DWORD next_game_tick = GetTickCount();
    int loops;
    float interpolation;

	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			done = true;
			break;
		}

        loops = 0;
        while(GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP) {
			result = Update();
			if (!result) break;
            next_game_tick += SKIP_TICKS;
            loops++;
        }

		if (!result) {
			done = true;
			break;
		}

        m_Interpolation = float(GetTickCount() + SKIP_TICKS - next_game_tick) / float( SKIP_TICKS );

		result = Render();
		if (!result) {
			done = true;
			break;
		}
	}
}

bool CSystem::Render() {
	renderCallback();

	return true;
}

bool CSystem::Update() {
	m_InputManager->Update();

	if (m_InputManager->isKeyPressed(KEY_ESCAPE)) {
		return false;
	}

	updateCallback();

	return true;
}

void CSystem::setCallback(CSystemEvent type, SystemEventHandler callback) {
	switch (type) {
		case EVENT_RENDER:
			renderCallback = callback;
		break;

		case EVENT_UPDATE:
			updateCallback = callback;
		break;

		case EVENT_INIT:
			initCallback = callback;
		break;

		case EVENT_SHUTDOWN:
			shutdownCallback = callback;
		break;
	}
}

float CSystem::getInterpolation() {
	return m_Interpolation;
	//return 0;
}

CWindow* CSystem::getWindow() {
	return m_Window;
}

CInputManager* CSystem::getInputManager() {
	return m_InputManager;
}

CRender* CSystem::getRender() {
	return m_Render;
}

CResourceManager* CSystem::getResourceManager() {
	return m_ResourceManager;
}