#include "stdafx.h"
#include "LineMgr.h"
#include "Line.h"
#include "MainFrm.h"
#include "MFCToolView.h"

IMPLEMENT_SINGLETON(CLineMgr);
CLineMgr::CLineMgr()
	: m_bCheck(true)
{
	ZeroMemory(m_vLinePos, sizeof(D3DXVECTOR2) * 2);
}


CLineMgr::~CLineMgr()
{
	Release_Line();
}

void CLineMgr::Add_Line(D3DXVECTOR3 vMouse)
{
	POINT pt = { vMouse.x, vMouse.y };

	if (m_bCheck)
	{
		m_vLinePos[0].x = (float)pt.x;
		m_vLinePos[0].y = (float)pt.y;
		m_bCheck = false;
	}
	else
	{
		m_vLinePos[1].x = (float)pt.x;
		m_vLinePos[1].y = (float)pt.y;

		m_listLine.emplace_back(new CLine(m_vLinePos[0], m_vLinePos[1]));

		m_bCheck = true;
		
		ZeroMemory(m_vLinePos, sizeof(D3DXVECTOR2) * 2);
	}
}

void CLineMgr::Add_Line(CLine* pLine)
{
	m_listLine.emplace_back(pLine);
}

void CLineMgr::Pop_Back()
{
	if (m_listLine.size() > 0)
	{
		Safe_Delete(m_listLine.back());
		m_listLine.pop_back();
	}
}

void CLineMgr::Render_Line()
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

		m_vLinePos[1].x = (float)pt.x;
		m_vLinePos[1].y = (float)pt.y;

		D3DXVECTOR2 vLinePos[2] =
		{
			{ m_vLinePos[0].x - pView->GetScrollPos(SB_HORZ), m_vLinePos[0].y - pView->GetScrollPos(SB_VERT) },
			{ m_vLinePos[1].x - pView->GetScrollPos(SB_HORZ), m_vLinePos[1].y - pView->GetScrollPos(SB_VERT) }
		};

		CGraphic_Device::Get_Instance()->Get_Line()->Draw(vLinePos, 2, D3DCOLOR_XRGB(0,0,0));
	}
	for (auto& pLine : m_listLine)
		pLine->Render_Line();
}

void CLineMgr::Release_Line()
{
	for_each(m_listLine.begin(), m_listLine.end(), Safe_Delete<CLine*>);
	m_listLine.clear();
}
