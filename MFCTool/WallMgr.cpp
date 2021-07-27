#include "stdafx.h"
#include "WallMgr.h"
#include "Wall.h"
#include "MainFrm.h"
#include "MFCToolView.h"

IMPLEMENT_SINGLETON(CWallMgr);
CWallMgr::CWallMgr()
	: m_bCheck(true)
{
	ZeroMemory(m_vRectPos, sizeof(D3DXVECTOR2) * 5);
}


CWallMgr::~CWallMgr()
{
	Release_Wall();
}

void CWallMgr::Add_Wall(D3DXVECTOR3 vMouse)
{
	POINT pt = { vMouse.x, vMouse.y };

	if (m_bCheck)
	{
		m_vRectPos[0] = { (float)pt.x, (float)pt.y };
		m_bCheck = false;
	}
	else
	{
		m_vRectPos[2] = { (float)pt.x, (float)pt.y };
		m_vRectPos[1] = { m_vRectPos[2].x, m_vRectPos[0].y };
		m_vRectPos[3] = { m_vRectPos[0].x, m_vRectPos[2].y };
		m_vRectPos[4] = m_vRectPos[0];

		m_listWall.emplace_back(CWall::Create(m_vRectPos[0], m_vRectPos[2]));

		m_bCheck = true;
		
		ZeroMemory(m_vRectPos, sizeof(D3DXVECTOR2) * 5);
	}
}

void CWallMgr::Add_Wall(CWall * pWall)
{
	m_listWall.emplace_back(pWall);
}

void CWallMgr::Pop_Back()
{
	if (m_listWall.size() > 0)
	{
		Safe_Delete(m_listWall.back());
		m_listWall.pop_back();
	}
}

void CWallMgr::Render_Wall()
{
	if (!m_bCheck)
	{
		CMainFrame* pMain = static_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		CMFCToolView* pView = static_cast<CMFCToolView*>(pMain->m_tMainSplitter.GetPane(0, 1));

		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(pView->m_hWnd, &pt);
		pt.x += pView->GetScrollPos(SB_HORZ);
		pt.y += pView->GetScrollPos(SB_VERT);

		m_vRectPos[2] = { (float)pt.x, (float)pt.y };
		m_vRectPos[1] = { m_vRectPos[2].x, m_vRectPos[0].y };
		m_vRectPos[3] = { m_vRectPos[0].x, m_vRectPos[2].y };
		m_vRectPos[4] = m_vRectPos[0];

		D3DXVECTOR2 vWallPos[5] = {};

		for (int i = 0; i < 5; ++i)
			vWallPos[i] = { m_vRectPos[i].x - pView->GetScrollPos(SB_HORZ), m_vRectPos[i].y - pView->GetScrollPos(SB_VERT) };

		CGraphic_Device::Get_Instance()->Get_Line()->Draw(vWallPos, 5, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (auto& pWall : m_listWall)
		pWall->Render_Wall();
}

void CWallMgr::Release_Wall()
{
	for_each(m_listWall.begin(), m_listWall.end(), Safe_Delete<CWall*>);
	m_listWall.clear();
}
