#pragma once

#include <string>
#include <Windows.h>

class CWindow {
public:
	CWindow();
	CWindow(std::string title, HINSTANCE hInstance, int width=800, int height=600, bool isWindowed = true);

	~CWindow();

	HRESULT Initialize(std::string title, HINSTANCE hInstance, int width=800, int height=600, bool isWindowed = true);
	void Shutdown();

	int getWidth();
	int getHeight();

	bool isWindowed();

	std::string getTitle();
	void setTitle(std::string title);

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	HWND getHandle();
protected:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	WINDOWPLACEMENT m_wp;

	bool m_isWindowed;
	std::string m_Title;
	
	int m_Width, m_Height;
};

static CWindow* WindowHandle = 0;
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);