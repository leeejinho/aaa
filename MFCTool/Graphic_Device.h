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
	//��ġ�� �ʱ�ȭ �ϴ� ����. 
	//1.��ġ�� ������ ���´�. 
	//2.��ġ�� �ʱⰪ�� �־��ش�. 
	//3. �� �������� ���� ��ġ(�׷��� ī��)�� �����ϱ� ���� �İ�ü�� �����Ѵ�. 
	LPDIRECT3D9  m_pSDK; // ��ġ�� ������ �����ϱ� ���� �İ�ü. 
	LPDIRECT3DDEVICE9 m_pDevice; // ��ġ�� �����ϴ� �İ�ü. 
	LPD3DXSPRITE	m_pSprite; 
	LPD3DXFONT		m_pFont; 

};

