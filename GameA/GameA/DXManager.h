#pragma once
#include "Sprite.h"
#include "Information.h"
#include <string>

using namespace std;
class CDXManager
{
public:
	CDXManager(void);
	~CDXManager(void);
	LPDIRECT3D9 m_directX;
	LPDIRECT3DDEVICE9 m_directXDevice;	
	LPD3DXSPRITE m_ppSprite;
	IDirect3DSurface9* m_backBuffer;
	bool InitDirectX(HWND hWnd);
	void ReleaseDevice();
	void BeginDraw();
	void EndDraw();
	void ClearScreen();
	IDirect3DSurface9 *CreateSurfaceFromFile(char* filename);
	CSprite *CreateSpriteFromFile(char *filename,D3DCOLOR color);
	void ShowSurface(IDirect3DSurface9 *surface,const RECT *srcrect,const RECT *desRect);
};

