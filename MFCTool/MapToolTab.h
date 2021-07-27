#pragma once
#include "afxcmn.h"


// CMapToolTab ��ȭ �����Դϴ�.
#include "MapTool.h"
class CMapToolTab : public CDialog
{
	DECLARE_DYNAMIC(CMapToolTab)

public:
	CMapToolTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMapToolTab();
public:
	CMapTool* m_pMapTool;
	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOLTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
};
