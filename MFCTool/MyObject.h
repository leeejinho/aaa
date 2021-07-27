#pragma once
class CMFCToolView;
class CMyObject
{
private:
	CMyObject();
public:
	~CMyObject();

public:
	vector<OBJECT*>& Get_ObjData() { return m_vecObject; }
public:
	void Set_View(CMFCToolView* pView) { m_pView = pView; }
public:
	void Add_Object(const D3DXVECTOR3& vMouse, const D3DXVECTOR3& vSize, const DWORD& dwDrawID);
	void Save_Objects();
	void Load_Objects();

	void Set_PosX(float _x) { m_PointX = _x; }
	void Set_PosY(float _y) { m_PointY = _y; }
	const float& Get_PosX() const { return m_PointX; }
	const float& Get_PosY() const { return m_PointY; }
public:
	HRESULT Ready();
	void	Render();
	void	Release();
public:
	static CMyObject* Create();
private:
	vector<OBJECT*> m_vecObject;
	CMFCToolView* m_pView;

	float m_PointX;
	float m_PointY;
};

