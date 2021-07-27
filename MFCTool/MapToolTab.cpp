// MapToolTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MapToolTab.h"
#include "afxdialogex.h"

// CMapToolTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapToolTab, CDialog)

CMapToolTab::CMapToolTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAPTOOLTAB, pParent)
{

}

CMapToolTab::~CMapToolTab()
{
}

void CMapToolTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(CMapToolTab, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMapToolTab::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CMapToolTab 메시지 처리기입니다.


void CMapToolTab::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int Sel = m_Tab.GetCurSel();

	switch (Sel)
	{
	case 0:
		m_pMapTool->ShowWindow(SW_SHOW);
		break;
	}

	*pResult = 0;
}


BOOL CMapToolTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CRect rc;
	m_Tab.GetWindowRect(rc);
	
	m_Tab.InsertItem(0, L"MapTool");
	//m_Tab.InsertItem(1, L"test");
	
	m_Tab.SetCurSel(0);

	m_pMapTool = new CMapTool;
	m_pMapTool->Create(IDD_MAPTOOL, &m_Tab);
	m_pMapTool->MoveWindow(0, 20, rc.Width() - 5, rc.Height() - 5);
	m_pMapTool->ShowWindow(SW_SHOW);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMapToolTab::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	for (int i = 0; i < 2; ++i)
		m_pMapTool->m_Radio[i].SetCheck(FALSE);
	CDialogEx::OnCancel();
}
