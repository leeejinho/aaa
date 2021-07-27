#include "stdafx.h"
#include "Graphic_Device.h"

IMPLEMENT_SINGLETON(CGraphic_Device)
CGraphic_Device::CGraphic_Device()
	:m_pSDK(nullptr)
	,m_pDevice(nullptr)
	,m_pFont(nullptr)
{
}


CGraphic_Device::~CGraphic_Device()
{
	Release_Graphic_Device(); 
}

HRESULT CGraphic_Device::Ready_Graphic_Device()
{
	//1.장치의 수준을 얻어온다. 
	D3DCAPS9 d3dcaps; 
	ZeroMemory(&d3dcaps, sizeof(D3DCAPS9)); 
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dcaps)))
		goto ERR; 

	DWORD vp = 0; 
	if (d3dcaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; 

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS)); 
	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight= WINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	 // D3DSWAPEFFECT_DISCARD - 스왑체인 방식을 사용하겠다. 
	 // 전면과 후면 버퍼를 준비하고 후면버퍼를 비운후 그림을 그리고 다 그린다면 
	 //전면 버퍼와 교체하는 방식. 
	 // 더블버퍼링 상위 호환이라고 생각하면 되겠다. 
	 d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	 d3dpp.hDeviceWindow = g_hWND;
	 d3dpp.Windowed = TRUE; // 투루면 창모드, 펄스면 전체화면 모드. 
	 // 근데 엠엡씨는 창모드밖에 안되요. 알게쬬 ? 
	 d3dpp.EnableAutoDepthStencil = TRUE;
	 d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	/* FullScreen_RefreshRateInHz must be zero for Windowed mode */
	 d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	 d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	 if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWND, vp, &d3dpp, &m_pDevice)))
		 goto ERR; 

	 if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
		 goto ERR;

	 D3DXFONT_DESCW tFontInfo; 
	 ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW)); 
	 tFontInfo.Height = 20; 
	 tFontInfo.Width = 20; 
	 tFontInfo.Weight = FW_HEAVY;
	 tFontInfo.CharSet = HANGEUL_CHARSET;
	 lstrcpy(tFontInfo.FaceName, L"CookieRunOTF Black"); 

	 if (FAILED(D3DXCreateFontIndirectW(m_pDevice, &tFontInfo, &m_pFont)))
		 goto ERR; 

	return S_OK;
ERR:
	ERR_MSG(L"System Error - Graphic_Device");
	return E_FAIL; 
}

void CGraphic_Device::Release_Graphic_Device()
{
	// 순서 중요. 레퍼런스 카운트 라는 기법을 사용하고 있기 때문에 순서가 맞춰지지 않으면 
	// 제대로 지워 지지 않는다. 
	// 그래서 내가 지금 말한대로 디바이스에서 SDK를 참조하여 사용하고 있기 때문에. 
	// 참조하는 대상먼저. 제거 되야 . 다음 제대로 지워질수 있다. 
	if (m_pFont)
		m_pFont->Release(); 

	if (m_pSprite)
		m_pSprite->Release(); 

	if (m_pDevice)
		m_pDevice->Release(); 

	if (m_pSDK)
		m_pSDK->Release(); 
}

void CGraphic_Device::Render_Begin()
{
	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	
}

void CGraphic_Device::Render_End(HWND hWnd /*= nullptr*/)
{
	m_pSprite->End();
	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);
}
