#pragma once
class CGraphic_Device final 
{
	DECLARE_SINGLETON(CGraphic_Device)
private:
	CGraphic_Device();
	~CGraphic_Device();
public:
	LPDIRECT3DDEVICE9 Get_Device() { return m_pDevice; }
	LPD3DXSPRITE Get_Sprite() { return m_pSprite;  }
	LPD3DXFONT Get_Font() { return m_pFont; }
public:
	HRESULT Ready_Graphic_Device(); 
	void Release_Graphic_Device(); 
	void Render_Begin(); 
	void Render_End(HWND hWnd = nullptr); 
private:
	//장치를 초기화 하는 과정. 
	//1.장치의 수준을 얻어온다. 
	//2.장치에 초기값을 넣어준다. 
	//3. 이 정보들을 토대로 장치(그래픽 카드)를 제어하기 위한 컴객체를 생성한다. 
	LPDIRECT3D9  m_pSDK; // 장치의 수준을 조사하기 위한 컴객체. 
	LPDIRECT3DDEVICE9 m_pDevice; // 장치를 제어하는 컴객체. 
	LPD3DXSPRITE	m_pSprite; 
	LPD3DXFONT		m_pFont; 

};

