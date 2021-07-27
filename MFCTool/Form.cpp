// Form.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "Form.h"


// CForm

IMPLEMENT_DYNCREATE(CForm, CFormView)

CForm::CForm()
	: CFormView(IDD_FORM)
{

}

CForm::~CForm()
{
}

void CForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CForm::OnBnClickedUnitTool)
	ON_BN_CLICKED(IDC_BUTTON6, &CForm::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CForm::OnBnClickedObjectTool)
END_MESSAGE_MAP()


// CForm 진단입니다.

#ifdef _DEBUG
void CForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CForm 메시지 처리기입니다.

//UnitTool 
void CForm::OnBnClickedUnitTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//ERR_MSG(L"성연아 왜 거기서 서성연?ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ"); 
	if (m_tUnitTool.GetSafeHwnd() == nullptr)
		m_tUnitTool.Create(IDD_UNITTOOL); 

	m_tUnitTool.ShowWindow(SW_SHOW);
}

//MapTool 
void CForm::OnBnClickedButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_tMapToolTab.GetSafeHwnd() == nullptr)
		m_tMapToolTab.Create(IDD_MAPTOOLTAB);

	m_tMapToolTab.ShowWindow(SW_SHOW);
}


void CForm::OnBnClickedObjectTool()
{
	if (m_tObjectTool.GetSafeHwnd() == nullptr)
		m_tObjectTool.Create(IDD_OBJECTTOOL);

	m_tObjectTool.ShowWindow(SW_SHOW);
}
