// Form.cpp : 姥薄 督析脊艦陥.
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


// CForm 遭舘脊艦陥.

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


// CForm 五獣走 坦軒奄脊艦陥.

//UnitTool 
void CForm::OnBnClickedUnitTool()
{
	// TODO: 食奄拭 珍闘継 硝顕 坦軒奄 坪球研 蓄亜杯艦陥.
	//ERR_MSG(L"失尻焼 訊 暗奄辞 辞失尻?せせせせせせせせせせせせせ"); 
	if (m_tUnitTool.GetSafeHwnd() == nullptr)
		m_tUnitTool.Create(IDD_UNITTOOL); 

	m_tUnitTool.ShowWindow(SW_SHOW);
}

//MapTool 
void CForm::OnBnClickedButton6()
{
	// TODO: 食奄拭 珍闘継 硝顕 坦軒奄 坪球研 蓄亜杯艦陥.
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
