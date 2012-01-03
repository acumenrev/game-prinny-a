#pragma once
#include"d3dx9.h"
#include"d3d9.h"
#include "Information.h"
class CSprite
{
public:
	// variables
	LPD3DXSPRITE m_spriteHandler;
	LPDIRECT3DTEXTURE9 m_texture;
	D3DXIMAGE_INFO m_info;
	CSprite(void);
	~CSprite(void);
	CSprite(LPDIRECT3DDEVICE9 d3ddev, char* fileName, D3DCOLOR color);
	void Render(float fX, float fY);
	void Render(float fX, float fY, D3DCOLOR color);
	void Render(float fX, float fY, RECT rect, D3DCOLOR color);
	void Render(float fX, float fY, RECT rect, D3DCOLOR color, float rotate);
	void Render(float fX, float fY, RECT rect, D3DCOLOR color, float rotate, float Xscaling, float yScaling);
};

class AllSprite
{
public:
	AllSprite(LPDIRECT3DDEVICE9 d3ddev)
	{
		// load all sprites in here
	}
};
