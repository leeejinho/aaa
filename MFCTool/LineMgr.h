#pragma once
class CLine;
class CLineMgr final
{
	DECLARE_SINGLETON(CLineMgr);
private:
	CLineMgr();
	~CLineMgr();
public:
	void Add_Line(D3DXVECTOR3 vMouse);
	void Add_Line(CLine* pLine);
	void Pop_Back();
public:
	void Render_Line();
	void Release_Line();
public:
	list<CLine*> Get_List() { return m_listLine; }
private:
	list<CLine*> m_listLine;
	D3DXVECTOR2	 m_vLinePos[2];
	bool		 m_bCheck;
};

