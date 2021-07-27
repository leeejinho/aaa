#pragma once
#include "afxwin.h"


// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
