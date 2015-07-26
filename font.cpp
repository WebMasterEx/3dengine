#include "font.h"

CFont::CFont() {
	m_Font = NULL;
}

CFont::~CFont() {

}

BOOL CFont::Initialize(LPDIRECT3DDEVICE9 device, char* faceName, int size, BOOL bold, BOOL italic) {
	HRESULT hr = 0;
	hr = D3DXCreateFont(device, -size, 0, bold ? 800 : 0, 1, italic, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, faceName, &m_Font);
	
	if (FAILED(hr)) {
		return FALSE;
	}
	
	return TRUE;
}

void CFont::Print( char* text, int xPosition, int yPosition, DWORD color, LPD3DXSPRITE sprite, int textBoxWidth, int textBoxHeight, FONTALIGNMENT alignment ) {
	if (!m_Font) {
		return;
	}

	DWORD format = DT_EXPANDTABS;
	if (textBoxWidth == 0) {
		format |= DT_NOCLIP;
	}
	else {
		format |= DT_WORDBREAK;
		switch ( alignment ) {
			case FA_LEFT:
				format |= DT_LEFT;
			break;
			case FA_CENTER:
				format |= DT_CENTER;
			break;
			case FA_RIGHT:
				format |= DT_RIGHT;
			break;
			case FA_TOPRIGHT:
				format |= DT_RIGHT | DT_TOP;
			break;
			case FA_BOTTOMRIGHT:
				format |= DT_RIGHT | DT_BOTTOM;
			break;
			case FA_TOPLEFT:
				format |= DT_LEFT | DT_TOP;
			break;
			case FA_BOTTOMLEFT:
				format |= DT_LEFT | DT_BOTTOM;
			break;
		}
		if (textBoxHeight == 0)	{
			textBoxHeight = 2000;
		}
	}

	RECT rect = { xPosition, yPosition, xPosition + textBoxWidth, yPosition + textBoxHeight };
	m_Font->DrawText( sprite, text, -1, &rect, format, color );
}

void CFont::Shutdown() {
	if (m_Font) {
		m_Font->Release();
		m_Font = NULL;
	}
}