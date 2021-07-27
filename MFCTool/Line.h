#pragma once
class CLine final
{
public:
	CLine();
	CLine(D3DXVECTOR2& vLeftPos, D3DXVECTOR2& vRightPos, int Red = 0, int Green = 0, int Blue = 0);
	~CLine();
public:
	void Render_Line();
public:
	D3DXVECTOR2 Get_LinePos(int idx) { return m_vLinePos[idx]; }
private:
	D3DXVECTOR2 m_vLinePos[2];
	D3DCOLOR	m_Color;
};

