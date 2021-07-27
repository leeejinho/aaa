#pragma once
class CWall final
{
private:
	CWall();
public:
	~CWall();
public:
	HRESULT Ready_Wall(D3DXVECTOR2 vPos1, D3DXVECTOR2 vPos2);
	void Render_Wall();
public:
	D3DXVECTOR2 Get_RectPos(int iIdx) { return m_vRectPos[iIdx]; }
public:
	static CWall* Create(D3DXVECTOR2 vPos1, D3DXVECTOR2 vPos2);
private:
	D3DXVECTOR2 m_vRectPos[5];
	D3DCOLOR	m_Color;
};

