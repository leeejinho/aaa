#pragma once
class CWall;
class CWallMgr final
{
	DECLARE_SINGLETON(CWallMgr);
public:
	CWallMgr();
	~CWallMgr();
public:
	void Add_Wall(D3DXVECTOR3 vMouse);
	void Add_Wall(CWall* pWall);
	void Pop_Back();
public:
	void Render_Wall();
	void Release_Wall();
public:
	list<CWall*>& Get_List() { return m_listWall; }
private:
	list<CWall*> m_listWall;
	D3DXVECTOR2	 m_vRectPos[5];
	bool		 m_bCheck;
};

