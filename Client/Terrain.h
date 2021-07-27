#pragma once
#include "GameObject.h"
class CTerrain final : public CGameObject
{
private:
	CTerrain();
public:
	~CTerrain();
public:
	vector<TILE*>& Get_TileData() { return m_vecTile; }
public:
	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;
public:
	static CTerrain* Create(); 
private:
	vector<TILE*> m_vecTile; 



};

