#pragma once
#include "afxwin.h"


// CUnitTool 대화 상자입니다.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// UnitTestData
	CString m_wstrSource;
	CString m_wstrDest;
	afx_msg void OnBnClickedCopy();
	map<wstring, UNITINFO*> m_mapUnitInfo; 
	afx_msg void OnBnClickedButton2();
	CString m_wstrName;
	int m_iAtt;
	int m_iDef;
	CListBox m_ListBox;
	afx_msg void OnLbnSelchangeFindUnit();
	CButton m_Radio[3];
	CButton m_CheckBox[3];
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
