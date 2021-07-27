// MapToolTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MapToolTab.h"
#include "afxdialogex.h"

// CMapToolTab ��ȭ �����Դϴ�.

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


// CMapToolTab �޽��� ó�����Դϴ�.


void CMapToolTab::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CMapToolTab::OnCancel()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	for (int i = 0; i < 2; ++i)
		m_pMapTool->m_Radio[i].SetCheck(FALSE);
	CDialogEx::OnCancel();
}
