#pragma once
#include "Scene.h"
class CStage final:
	public CScene
{
private:
	CStage();
public:
	virtual ~CStage();
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Ready_Scene() override;
	virtual int Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;
public:
	static CScene* Create();
private:
	CGameObject_Manager* m_pGameObject_Manager; 


};

