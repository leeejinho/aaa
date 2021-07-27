#pragma once

class CGameObject; 
class CScene_Manager; 
class CMainApp final
{
private:
	CMainApp();
public:
	~CMainApp();

public:
	HRESULT Ready_MainApp(); 
	void Update_MainApp(); 
	void Render_MainApp(); 
	void Release_MainApp(); 
public:
	static CMainApp* Create();
private:
	CGraphic_Device* m_pGraphicDevice; 
	CTexture_Manager* m_pTexture_Manager; 
	CScene_Manager* m_pScene_Manager; 
};

// class CTest : public CMainApp
// {

//};