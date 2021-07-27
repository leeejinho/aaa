#include "stdafx.h"
#include "Line.h"
#include "MainFrm.h"
#include "MFCToolView.h"

CLine::CLine()
{
}

CLine::CLine(D3DXVECTOR2 & vLeftPos, D3DXVECTOR2 & vRightPos, int Red, int Green, int Blue)
{
	m_vLinePos[0] = vLeftPos;
	m_vLinePos[1] = vRightPos;
	m_Color = D3DCOLOR_XRGB(Red, Green, Blue);
}


CLine::~CLine()
{
}

void CLine::Render_Line()
{
	CMainFrame* pMain = static_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = static_cast<CMFCToolView*>(pMain->m_tMainSplitter.GetPane(0, 1));

	D3DXVECTOR2 vLinePos[2] = 
	{
		{ m_vLinePos[0].x - pView->GetScrollPos(SB_HORZ), m_vLinePos[0].y - pView->GetScrollPos(SB_VERT) },
		{ m_vLinePos[1].x - pView->GetScrollPos(SB_HORZ), m_vLinePos[1].y - pView->GetScrollPos(SB_VERT) }
	};

	CGraphic_Device::Get_Instance()->Get_Line()->Draw(vLinePos, 2, m_Color);
}
