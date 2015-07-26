#pragma once

#include <string>
#include <Windows.h>
#include "dxu.h"

enum FONTALIGNMENT { FA_LEFT, FA_CENTER, FA_RIGHT, FA_TOPRIGHT, FA_TOPLEFT, FA_BOTTOMRIGHT, FA_BOTTOMLEFT }; 

class CFont  { 
public: 
    CFont(); 
	~CFont();
    BOOL Initialize(LPDIRECT3DDEVICE9 device, char* faceName, int size, BOOL bold = FALSE, BOOL italic = FALSE ); 

    void Print(char* text, int xPosition, int yPosition, DWORD color, LPD3DXSPRITE sprite = NULL,int textBoxWidth = 0, int textBoxHeight = 0, FONTALIGNMENT alignment = FA_LEFT); 
    //void OnLostDevice(); 
    //void OnResetDevice(); 
    void Shutdown(); 

private: 
    LPD3DXFONT m_Font; 
}; 