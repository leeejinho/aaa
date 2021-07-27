#pragma once
#include "afxwin.h"


// CObjectTool dialog
class CMyObject;
class CObjectTool : public CDialog
{
	DECLARE_DYNAMIC(CObjectTool)

public:
	CObjectTool(CWnd* pParent = NULL);   // standard constructor
	virtual ~CObjectTool();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	static void Set_MyObject(CMyObject* pMyObj) { m_pMyObject = pMyObj; }
public:
	afx_msg void OnLbnSelchangePicture();
	CListBox m_ListBox;
	afx_msg void OnBnClickedButton1();
	CStatic m_Picture;

	map<wstring, OBJECT*> m_mapObjInfo;
	vector<CString> m_vecFilePath;
	CString m_wstrType;
	CString m_pObjectKey;
	static CMyObject* m_pMyObject;

	DWORD m_dwDrawID;
	CButton m_Radio[3];
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CListBox m_ObjListBox;
	afx_msg void OnLbnSelchangePicture2();
	//afx_msg void OnBnClickedAddObj();
	CString m_wstrPointX;
	CString m_wstrPointY;
	afx_msg void OnBnClickedRefresh();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedButtonLoad();
};
