#pragma once
#include "GameObject.h"
class CPlayer final :
	public CGameObject
{
private:
	CPlayer();
public:
	virtual ~CPlayer();
public:
	void WriteMatrix(); 
public:
	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;
public:
	static CGameObject* Create();
private:
	float		m_fSpeed	;
	D3DXVECTOR3 m_vQ[4]		; 
	D3DXVECTOR3 m_vP[4]		; 
	float		m_fAngle		; 
};

