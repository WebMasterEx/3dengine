#include "cwindow.h"

CWindow::CWindow() {
	m_hWnd = NULL;
	m_isWindowed = true;
}

CWindow::CWindow(std::string title, HINSTANCE hInstance, int width, int height, bool isWindowed) {
	m_hWnd = NULL;
	m_isWindowed = true;

	Initialize(title, hInstance, width, height, isWindowed);
}

CWindow::~CWindow() {

}

HRESULT CWindow::Initialize(std::string title, HINSTANCE hInstance, int width, int height, bool isWindowed) {
	HRESULT hr = S_OK;

	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;

	m_Title = title;
	m_hInstance = hInstance;
	m_isWindowed = isWindowed;

	int posX, posY;

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = title.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	if (!isWindowed) {
		width  = GetSystemMetrics(SM_CXSCREEN);
		height = GetSystemMetrics(SM_CYSCREEN);
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));

		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)width;
		dmScreenSettings.dmPelsHeight = (unsigned long)height;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		posX = posY = 0;
	}
	else {
		width = 800;
		height = 600;

		posX = (GetSystemMetrics(SM_CXSCREEN) - width)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	}

	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, title.c_str(), title.c_str(), 
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, width, height, NULL, NULL, hInstance, NULL);

	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);
	ShowCursor(false);

	RECT rect;
	GetWindowRect(m_hWnd, &rect);

	ClipCursor(&rect);

	m_Width = width;
	m_Height = height;

	return hr;
}

void CWindow::Shutdown() {
	ShowCursor(true);

	if(!m_isWindowed) {
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(m_hWnd);
	m_hWnd = NULL;

	UnregisterClass(m_Title.c_str(), m_hInstance);

	m_hInstance = NULL;
	WindowHandle = NULL;
}

LRESULT CALLBACK CWindow::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	switch(umsg) {
		case WM_KEYDOWN:
			return 0;
		break;

		case WM_KEYUP:
			return 0;
		break;

		default:
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		break;
	}
}

HWND CWindow::getHandle() {
	return m_hWnd;
}

int CWindow::getWidth() {
	return m_Width;
}

int CWindow::getHeight() {
	return m_Height;
}

bool CWindow::isWindowed() {
	return m_isWindowed;
}

std::string CWindow::getTitle() {
	return m_Title;
}

void CWindow::setTitle(std::string title) {
	SetWindowText(m_hWnd, title.c_str());
	m_Title = title;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	switch(umessage) {
		// Check if the window is being destroyed.
		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE: {
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default: {
			return WindowHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}