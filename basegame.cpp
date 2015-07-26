#include "basegame.h"

CBaseGame::CBaseGame() {
	m_System = NULL;
	m_Render = NULL;
	m_InputManager = NULL;
	m_ResourceManager = NULL;
	m_Camera = NULL;
}

CBaseGame::~CBaseGame() {

}

void CBaseGame::setEngine(CSystem* engine) {
	m_System = engine;
}

bool CBaseGame::Init() {
	m_Render = m_System->getRender();
	m_InputManager = m_System->getInputManager();
	m_ResourceManager = m_System->getResourceManager();
	m_Window = m_System->getWindow();

	m_Camera = new CCamera(D3DXVECTOR3(0, 0, -25));

	return true;
}

bool CBaseGame::Update() {
	m_Camera->Yaw(m_InputManager->getMouseX()*0.005);
	m_Camera->Pitch(m_InputManager->getMouseY()*0.005);

	if (m_InputManager->isKeyPressed(KEY_W)) {
		m_Camera->MoveForward(5);
	}

	if (m_InputManager->isKeyPressed(KEY_S)) {
		m_Camera->MoveForward(-5);
	}

	if (m_InputManager->isKeyPressed(KEY_D)) {
		m_Camera->MoveRight(5);
	}

	if (m_InputManager->isKeyPressed(KEY_A)) {
		m_Camera->MoveRight(-5);
	}

	return true;
}

bool CBaseGame::Render(float interpolation) {
	return true;
}

bool CBaseGame::Shutdown() {
	return true;
}