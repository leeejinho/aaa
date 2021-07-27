#include "stdafx.h"
#include "Stage.h"
#include "Terrain.h"

CStage::CStage()
	:m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
{
}


CStage::~CStage()
{
	Release_Scene();
}

HRESULT CStage::Ready_Scene()
{
	CGameObject* pObject = CTerrain::Create(); 
	m_pGameObject_Manager->Add_GameObject_Manager(CGameObject_Manager::TERRAIN, pObject); 
	return S_OK;
}

int CStage::Update_Scene()
{
	m_pGameObject_Manager->Update_GameObject_Manager(); 
	m_pGameObject_Manager->Late_Update_GameObject_Manager(); 
	return 0;
}

void CStage::Render_Scene()
{
	m_pGameObject_Manager->Render_GameObject_Manager(); 
}

void CStage::Release_Scene()
{
}

CScene * CStage::Create()
{
	CScene* pInstance = new CStage;
	if (FAILED(pInstance->Ready_Scene()))
		Safe_Delete(pInstance);

	return pInstance;
}
