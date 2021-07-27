#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
	:m_fSpeed(0.f)
	, m_fAngle(0.f)
{
	ZeroMemory(m_vP, sizeof(D3DXVECTOR3) * 4);
	ZeroMemory(m_vQ, sizeof(D3DXVECTOR3) * 4);
}


CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_GameObject()
{
	m_tInfo.vPos = { 100.f, 0.f, 0.f }; 
	m_tInfo.vDir = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(100.f, 100.f, 0.f); 
	m_fSpeed = 2.f; 
	// 좌측 상단 
	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f }; 
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

// 	for (int i = 0; i < 4; ++i)
// 		m_vP[i] += m_tInfo.vPos; 
	return S_OK;
}

int CPlayer::Update_GameObject()
{
	m_fAngle += m_fSpeed; 
	D3DXMATRIX matParentTrans; 
	
	D3DXMatrixTranslation(&matParentTrans, 400.f, 300.f, 0.f);
	
	D3DXMATRIX matScale, matRotZ, matTrans, matRelRotZ, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRelRotZ, D3DXToRadian(m_fAngle));

	matWorld = matScale * matRotZ * matTrans * matRelRotZ * matParentTrans;
	//D3DXVec3TransformCoord(); // x,y,z w = 1
	//D3DXVec3TransformNormal(); // x,y,z w = 0

	//행렬을 이용한 객체 상태 표현. ! ////////////////////////////////////////////////////////////////////////
	m_fAngle += m_fSpeed;
	for (int i = 0; i < 4; ++i)
	{

		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld); 
	}

	return 0;
}

void CPlayer::Late_Update_GameObject()
{
}

void CPlayer::Render_GameObject()
{




}

void CPlayer::Release_GameObject()
{
}

CGameObject * CPlayer::Create()
{
	CGameObject* pInstance = new CPlayer; 
	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr; 
	}
	return pInstance;
}
