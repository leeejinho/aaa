#include "stdafx.h"
#include "MainApp.h"
#include "Scene_Manager.h"
#include "Player.h"

CMainApp::CMainApp()
	:m_pGraphicDevice(CGraphic_Device::Get_Instance())
	, m_pTexture_Manager(CTexture_Manager::Get_Instance())
	, m_pScene_Manager(CScene_Manager::Get_Instance())
{
}


CMainApp::~CMainApp()
{
	Release_MainApp(); 
}
//0x80004005
HRESULT CMainApp::Ready_MainApp()
{
	//1
	if (FAILED(m_pGraphicDevice->Ready_Graphic_Device(CGraphic_Device::WIN_MODE)))
		goto ERR;

	if (FAILED(m_pTexture_Manager->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Terrain/Tile/Tile%d.png", L"Terrain", L"Tile", 36)))
		goto ERR; 

	m_pScene_Manager->Change_Scene_Manager(CScene_Manager::SCENE_STAGE); 
	return S_OK; 
ERR:
	ERR_MSG(L"Ready MainApp Failed"); 
	return E_FAIL; 
}

void CMainApp::Update_MainApp()
{
	m_pScene_Manager->Update_Scene_Manager(); 
}

void CMainApp::Render_MainApp()
{
	m_pGraphicDevice->Render_Begin(); 
	m_pScene_Manager->Render_Scene_Manager(); 
	m_pGraphicDevice->Render_End(); 
}

void CMainApp::Release_MainApp()
{
	CGameObject_Manager::Destroy_Instance(); 
	m_pScene_Manager->Destroy_Instance(); 
	m_pTexture_Manager->Destroy_Instance(); 
	m_pGraphicDevice->Destroy_Instance(); 
}

CMainApp * CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp; 
	/*if (0x80000000 & pInstance->Ready_MainApp())*/
	if (FAILED(pInstance->Ready_MainApp()))
	{
		delete pInstance; 
		pInstance = nullptr; 
		return pInstance; 
	}
	return pInstance;
}
