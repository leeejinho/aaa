#pragma once
#include "afxcmn.h"


// CMapToolTab 대화 상자입니다.
#include "MapTool.h"
class CMapToolTab : public CDialog
{
	DECLARE_DYNAMIC(CMapToolTab)

public:
	CMapToolTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapToolTab();
public:
	CMapTool* m_pMapTool;
	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOLTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
};
