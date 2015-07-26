#include "cinputmanager.h"

CInputManager::CInputManager() {
	m_MouseState = NULL;
	m_DInput = NULL;
	m_Keyboard = NULL;
	m_Mouse = NULL;
}

CInputManager::~CInputManager() {

}

HRESULT CInputManager::Initialize(HWND hWnd) {
	HRESULT hr = S_OK;
	m_hWnd = hWnd;

	unsigned short i;

    ZeroMemory(&m_Keys, sizeof(BYTE)*256);
    //for(i = 0; i < 256; i++) m_NewKeyState[i] = true;
    ZeroMemory(&m_DInputMouseState, sizeof(DIMOUSESTATE2));
    //for(i = 0; i < 8; i++) m_NewKey[i] = true;

	hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_DInput, NULL);
	if (FAILED(hr)) {
		return hr;
	}

	hr = m_DInput->CreateDevice(GUID_SysKeyboard, &m_Keyboard, NULL);
	if (FAILED(hr)) {
		return hr;
	}

	hr = m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		return hr;
	}

	hr = m_Keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		return hr;
	}

	// Настройка мыши
	hr = m_DInput->CreateDevice(GUID_SysMouse, &m_Mouse, NULL);
	if (FAILED(hr)) {
		return hr;
	}

	hr = m_Mouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hr)) {
		return hr;
	}

	hr = m_Mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		return hr;
	}

	return hr;
}

void CInputManager::Update() {
    HRESULT hr;

	// Опрашиваем клавиатуру
    hr = m_Keyboard->GetDeviceState(sizeof(BYTE)*256, &m_Keys); // Данные с клавиатуры
    if(FAILED(hr)) {
        do {
			hr = m_Keyboard->Acquire(); // Захват
        }
        while (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED);
    }

	// Опрашиваем мышь
    hr = m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE2), &m_DInputMouseState); // Данные с мышки
    if(FAILED(hr)) {
        do{
			hr = m_Mouse->Acquire(); // Захват
        }
        while (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED);
	}
}

void CInputManager::Shutdown() {
	if(m_Keyboard) {
		m_Keyboard->Unacquire();
		m_Keyboard->Release();
		m_Keyboard = NULL;
	}

	if(m_Mouse) {
		m_Mouse->Unacquire();
		m_Mouse->Release();
		m_Mouse = NULL;
	}

	if(m_DInput) {
		m_DInput->Release();
		m_DInput = NULL;
	}
}

float CInputManager::getMouseX() {
	return (float)m_DInputMouseState.lX;
}

float CInputManager::getMouseY() {
	return (float)m_DInputMouseState.lY;
}

float CInputManager::getMouseZ() {
	return (float)m_DInputMouseState.lZ;
}

bool CInputManager::isKeyPressed(BYTE key) {
	if (m_Keys[key] & 0x80) return true;
	return false;
}