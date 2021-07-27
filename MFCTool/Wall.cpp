#include "stdafx.h"
#include "Wall.h"
#include "MainFrm.h"
#include "MFCToolView.h"

CWall::CWall()
{
}


CWall::~CWall()
{
}

HRESULT CWall::Ready_Wall(D3DXVECTOR2 vPos1, D3DXVECTOR2 vPos2)
{
	m_vRectPos[0] = vPos1;
	m_vRectPos[1] = { vPos2.x, vPos1.y };
	m_vRectPos[2] = vPos2;
	m_vRectPos[3] = { vPos1.x, vPos2.y };
	m_vRectPos[4] = vPos1;

	m_Color = D3DCOLOR_XRGB(0, 0, 0);
	return S_OK;
}

void CWall::Render_Wall()
{
	CMainFrame* pMain = static_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = static_cast<CMFCToolView*>(pMain->m_tMainSplitter.GetPane(0, 1));

	D3DXVECTOR2 vWallPos[5] = {};

	for (int i = 0; i < 5; ++i)
		vWallPos[i] = { m_vRectPos[i].x - pView->GetScrollPos(SB_HORZ), m_vRectPos[i].y - pView->GetScrollPos(SB_VERT) };

	CGraphic_Device::Get_Instance()->Get_Line()->Draw(vWallPos, 5, m_Color);
}

CWall * CWall::Create(D3DXVECTOR2 vPos1, D3DXVECTOR2 vPos2)
{
	CWall* pInstance = new CWall;
	if (FAILED(pInstance->Ready_Wall(vPos1, vPos2)))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
