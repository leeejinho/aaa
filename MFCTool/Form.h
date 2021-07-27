#pragma once



// CForm �� ���Դϴ�.
#include "UnitTool.h"
#include "MapTool.h"
#include "ObjectTool.h"
#include "MapToolTab.h"
class CForm : public CFormView
{
	DECLARE_DYNCREATE(CForm)

protected:
	CForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CForm();
public:
	CUnitTool m_tUnitTool;
	CMapTool m_tMapTool; 
	CMapToolTab m_tMapToolTab;
	CObjectTool m_tObjectTool;
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedUnitTool();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedObjectTool();
};


