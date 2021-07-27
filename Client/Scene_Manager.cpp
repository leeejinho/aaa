#include "stdafx.h"
#include "Scene_Manager.h"
#include "Stage.h"
IMPLEMENT_SINGLETON(CScene_Manager)
CScene_Manager::CScene_Manager()
{
}


CScene_Manager::~CScene_Manager()
{
	Release_Scene_Manager(); 
}

HRESULT CScene_Manager::Change_Scene_Manager(ID eScene)
{
	m_eNextScene = eScene; 
	if (m_eNextScene != m_eCurScene)
	{
		Safe_Delete(m_pScene); 
		switch (eScene)
		{
		case CScene_Manager::SCENE_LOADING:
			break;
		case CScene_Manager::SCENE_STAGE:
			m_pScene = CStage::Create(); 
			break;
		case CScene_Manager::SCENE_END:
			break;
		default:
			break;
		}
		m_eCurScene = m_eNextScene; 
	}
	return S_OK;
}

void CScene_Manager::Update_Scene_Manager()
{
	m_pScene->Update_Scene();
	
}

void CScene_Manager::Render_Scene_Manager()
{
	m_pScene->Render_Scene();
}

void CScene_Manager::Release_Scene_Manager()
{
	Safe_Delete(m_pScene); 
}
