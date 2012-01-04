#include "Sprite.h"

#pragma region Constructors & Destructor

/************************************************************************/
/*                             Constructor                              */
/************************************************************************/
CSprite::CSprite(void)
{
}
/************************************************************************/
/*                             Destructor                               */
/************************************************************************/
CSprite::~CSprite(void)
{
}
/************************************************************************/
/*                             Constructor                              */
/************************************************************************/
CSprite::CSprite(LPDIRECT3DDEVICE9 d3ddev, char* fileName, D3DCOLOR color)
{
	m_texture = NULL;
	HRESULT result = D3DXGetImageInfoFromFile(fileName,&m_info);
	if(result != D3D_OK)
	{
		return;
	}
	result = D3DXCreateSprite(d3ddev,&m_spriteHandler);
	result = D3DXCreateTextureFromFileEx(d3ddev,
		fileName,
		m_info.Width,
		m_info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		color,
		&m_info,
		NULL,
		&m_texture);
	if(result != D3D_OK)
	{
		return;
	}
}

#pragma endregion

#pragma region Methods

/************************************************************************/
/*                                Render                                */
/************************************************************************/
void CSprite::Render(float fX, float fY)
{
	D3DXVECTOR3 local(fX,fY,0);
	m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	m_spriteHandler->Draw(m_texture,
		NULL,
		NULL,
		&local,
		D3DCOLOR_ARGB(255,255,255,255));
	m_spriteHandler->End();
}
/************************************************************************/
/*                                Render                                */
/************************************************************************/
void CSprite::Render(float fX, float fY, D3DCOLOR color)
{
	D3DXVECTOR3 local(fX,fY,0);
	m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	m_spriteHandler->Draw(m_texture,
		NULL,
		NULL,
		&local,
		color);
	m_spriteHandler->End();
}
/************************************************************************/
/*                                Render                                */
/************************************************************************/
void CSprite::Render(float fX, float fY, RECT rect, D3DCOLOR color)
{
	rect.right++;
	rect.bottom++;
	D3DXVECTOR3 local(fX,fY,0);
	m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	m_spriteHandler->Draw(m_texture,
		&rect,
		NULL,
		&local,
		color);
	m_spriteHandler->End();
}
/************************************************************************/
/*                                Render                                */
/************************************************************************/
void CSprite::Render(float fX, float fY, RECT rect, D3DCOLOR color, float rotate)
{
	/*rect.right++;
	rect.bottom++;*/
	D3DXVECTOR2 pos(fX,fY);
	m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	float Rotate = rotate*D3DX_PI/180;
	D3DXMATRIX m1;
	D3DXVECTOR2 rotate_center;
	rotate_center.x = fX + (rect.right - rect.left)/2;
	rotate_center.y = fY + (rect.bottom - rect.top)/2;
	D3DXMatrixTransformation2D(&m1,
		NULL,
		0.0f,
		NULL,
		&rotate_center,
		Rotate,
		&pos);
	m_spriteHandler->SetTransform(&m1);
	m_spriteHandler->Draw(m_texture,
		&rect,
		NULL,
		NULL,
		color);
	D3DXMatrixIdentity(&m1);
	m_spriteHandler->SetTransform(&m1);
	m_spriteHandler->End();
}
/************************************************************************/
/*                                Render                                */
/************************************************************************/
void CSprite::Render(float fX, float fY, RECT rect, D3DCOLOR color, float rotate, float xScaling, float yScaling)
{
	/*rect.right++;
	rect.top++;*/
	D3DXVECTOR2 pos(fX,fY);
	D3DXVECTOR2 scaling(xScaling,yScaling);
	m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	float Rotate = rotate*D3DX_PI/180;
	D3DXMATRIX m1;
	D3DXVECTOR2 rotate_center;
	rotate_center.x = fX + (rect.right - rect.left)/2;
	rotate_center.y = fY + (rect.bottom - rect.top)/2;
	D3DXMatrixTransformation2D(&m1,
		NULL,
		NULL,
		&scaling,
		&rotate_center,
		Rotate,
		&pos);
	m_spriteHandler->SetTransform(&m1);
	m_spriteHandler->Draw(m_texture,
		&rect,
		NULL,
		NULL,
		color);
	D3DXMatrixIdentity(&m1);
	m_spriteHandler->SetTransform(&m1);
	m_spriteHandler->End();
}

#pragma endregion 