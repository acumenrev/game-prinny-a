#include "DXManager.h"

#pragma region Constructors & Destructor

CDXManager::CDXManager(void)
{
	m_directX=NULL;
	m_directXDevice=NULL;
	m_backBuffer=NULL;
}
//////////////////////////////////////////////////////////////////////////
CDXManager::~CDXManager(void)
{
	ReleaseDevice();
}
//////////////////////////////////////////////////////////////////////////
void CDXManager::ReleaseDevice()
{
	if(m_directX != NULL)
	{
		m_directX->Release();
	}
	if(m_directXDevice != NULL)
	{
		m_directXDevice->Release();
	}
}

#pragma endregion 

#pragma region Methods

/************************************************************************/
/*                              Init DirectX                            */
/************************************************************************/
bool CDXManager::InitDirectX(HWND hWnd)
{
	m_directX=NULL;
	m_directXDevice=NULL;
	if(NULL == (m_directX=Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return true;
	}
	D3DPRESENT_PARAMETERS present;
	ZeroMemory(&present,sizeof(present));
	present.BackBufferCount=1;
	present.BackBufferFormat=D3DFMT_X8R8G8B8;
	present.BackBufferHeight= WINDOW_HEIGHT;
	present.BackBufferWidth= WINDOW_WIDTH;
	present.hDeviceWindow= hWnd;
	present.SwapEffect=D3DSWAPEFFECT_DISCARD;
	present.Windowed=true;
	if(FAILED(m_directX->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&present,&m_directXDevice)))
	{
		if(FAILED(m_directX->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&present,&m_directXDevice)))
		{
				return false;
		}
	}
	
	m_directXDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&m_backBuffer);

	if(m_ppSprite == NULL)
		return false;
	return true;
}
/************************************************************************/
/*                               Begin Draw                             */
/************************************************************************/
void CDXManager::BeginDraw()
{
	if(m_directXDevice == NULL)
	{
		return;
	}
	m_directXDevice->BeginScene();
}
/************************************************************************/
/*                              End Draw                                */
/************************************************************************/
void CDXManager::EndDraw()
{
	m_directXDevice->EndScene();
	m_directXDevice->Present(NULL,NULL,NULL,NULL);
}
/************************************************************************/
/*                          Clear Screen                                */
/************************************************************************/
void CDXManager::ClearScreen()
{
	m_directXDevice->Clear(0,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0,0,0),
		1.0f,
		0);
}
/************************************************************************/
/*                           Create surface from file                   */
/************************************************************************/
IDirect3DSurface9* CDXManager::CreateSurfaceFromFile(char* fileName)
{
	HRESULT hResult;
	IDirect3DSurface9 *surface;
	D3DXIMAGE_INFO imageInfo;
	hResult=::D3DXGetImageInfoFromFile(fileName,&imageInfo);
	if(FAILED(hResult))
		return NULL;
	hResult= m_directXDevice->CreateOffscreenPlainSurface(imageInfo.Width,imageInfo.Height,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&surface,NULL);
	if(FAILED(hResult))
		return NULL;
	hResult=::D3DXLoadSurfaceFromFile(surface,NULL,NULL,fileName,NULL,D3DX_DEFAULT,D3DCOLOR_ARGB(255,255,255,255),NULL);
	if(FAILED(hResult))
		return NULL;
	return surface;
}
/************************************************************************/
/*                            Show Surface                              */
/************************************************************************/
void CDXManager::ShowSurface(IDirect3DSurface9 *surface,const RECT *srcrect,const RECT *desRect)
{
	m_directXDevice->StretchRect(surface,srcrect,m_backBuffer,desRect,D3DTEXF_NONE);
}
/************************************************************************/
/*                             Create Sprite from file                  */
/************************************************************************/
CSprite* CDXManager::CreateSpriteFromFile(char *filename,D3DCOLOR color)
{
	CSprite* sprite=new CSprite(m_directXDevice,filename,color);
	return sprite;
}

#pragma endregion