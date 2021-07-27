// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
	, m_wstrSource(_T(""))
	, m_wstrDest(_T(""))
	, m_wstrName(_T(""))
	, m_iAtt(0)
	, m_iDef(0)
{

}

CUnitTool::~CUnitTool()
{
	for (auto& rPair : m_mapUnitInfo)
		Safe_Delete(rPair.second); 
	m_mapUnitInfo.clear(); 
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_wstrSource);
	DDX_Text(pDX, IDC_EDIT2, m_wstrDest);
	DDX_Text(pDX, IDC_EDIT3, m_wstrName);
	DDX_Text(pDX, IDC_EDIT4, m_iAtt);
	/*DDV_MinMaxInt(pDX, m_iAtt, 0, 50);*/
	DDX_Text(pDX, IDC_EDIT5, m_iDef);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);

	DDX_Control(pDX, IDC_CHECK1, m_CheckBox[0]);
	DDX_Control(pDX, IDC_CHECK2, m_CheckBox[1]);
	DDX_Control(pDX, IDC_CHECK3, m_CheckBox[2]);

}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnBnClickedCopy)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnBnClickedButton2)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnLbnSelchangeFindUnit)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitTool::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CUnitTool::OnBnClickedButton5)
END_MESSAGE_MAP()


// CUnitTool �޽��� ó�����Դϴ�.


void CUnitTool::OnBnClickedCopy()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	/*
	���� true�� �־��شٸ� 
	���̾�α׿��� �����͸� ����. 
	*/
	m_wstrDest = m_wstrSource; 
	m_wstrSource = L"�� ��¼���"; 
	UpdateData(FALSE);
	/*
	���� false��� 
	�����͸� ���̾�α׿��� ����! 
	*/
}


//Add
void CUnitTool::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE); 
	auto& iter_find = m_mapUnitInfo.find(m_wstrName.GetString());
	if (iter_find != m_mapUnitInfo.end())
		return; 

	UNITINFO* pUnitInfo = new UNITINFO{};
	/*ZeroMemory(pUnitInfo, sizeof(UNITINFO)); �ȵ�*/
	for (int i = 0 ; i < 3; ++i)
	{
		// ���� ��ư�� �����ִ��� �ƴ����� �Ǻ��ϴ� �Լ�. 
		if (m_Radio[i].GetCheck())
		{
			pUnitInfo->byJob = i; 
			break; 
		}
	}
	//0000 0000
	//0000 0001
	//0000 0001 -> byItem 
	if (m_CheckBox[0].GetCheck())
		pUnitInfo->byItem |= ��; 
	//0000 0001
	//0000 0010
	//| 0000 0011
	if (m_CheckBox[1].GetCheck())
		pUnitInfo->byItem |= Ȱ; 
	if (m_CheckBox[2].GetCheck())
		pUnitInfo->byItem |= ��; 
	//0000 0111 

	pUnitInfo->wstrName = m_wstrName;
	pUnitInfo->iAtt = m_iAtt; 
	pUnitInfo->iDef = m_iDef; 
	m_mapUnitInfo.emplace(pUnitInfo->wstrName, pUnitInfo); 
	m_ListBox.AddString(pUnitInfo->wstrName); 
	UpdateData(FALSE); 
}


void CUnitTool::OnLbnSelchangeFindUnit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE); 
	for (int i = 0 ; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE); 
		m_CheckBox[i].SetCheck(FALSE);
	}
	// ����Ʈ�ڽ��� ���� ���õ� �ε��� ��ȣ�� ��ȯ . 
	int iIndex = m_ListBox.GetCurSel();
	CString wstrFindName; 

	m_ListBox.GetText(iIndex, wstrFindName); 
	auto& iter_find = m_mapUnitInfo.find(wstrFindName.GetString()); 
	if (m_mapUnitInfo.end() == iter_find)
		return; 
	m_wstrName = iter_find->second->wstrName; 
	m_iAtt = iter_find->second->iAtt; 
	m_iDef = iter_find->second->iDef;
	m_Radio[iter_find->second->byJob].SetCheck(TRUE); 
	//0000 0011
	//0000 0001
	//0000 0000 
	if (iter_find->second->byItem & ��)
		m_CheckBox[0].SetCheck(TRUE); 
	if (iter_find->second->byItem & Ȱ)
		m_CheckBox[1].SetCheck(TRUE); 
	if (iter_find->second->byItem & ��)
		m_CheckBox[2].SetCheck(TRUE); 
	UpdateData(FALSE); 
}

// Delete 
void CUnitTool::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE); 
	int iSelect = m_ListBox.GetCurSel(); 
	if (LB_ERR == iSelect)
		return; 
	
	CString wstrFindName; 
	m_ListBox.GetText(iSelect, wstrFindName); 

	auto& iter_Find = m_mapUnitInfo.find(wstrFindName.GetString()); 

	if (iter_Find == m_mapUnitInfo.end())
		return; 

	Safe_Delete(iter_Find->second); 
	m_mapUnitInfo.erase(iter_Find);
	m_ListBox.DeleteString(iSelect); 
	UpdateData(FALSE);
}

//Save
void CUnitTool::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog Dlg(FALSE,// ���� ���(TRUE) Ȥ�� ���� ���(FALSE) ��� �� ������. 
		L"dat",// ����Ʈ Ȯ���� �� 
		L"*.dat",// ����Ʈ ���� �̸� 
		OFN_OVERWRITEPROMPT);// â�� �⺻ ���¸� �������� �� ����. �ִ� �ߺ����� ����� ���޽��� �����.  
	TCHAR szFilePath[MAX_PATH]{}; 
	//D:\�ں���\119\FrameWork (6) (2)
	GetCurrentDirectory(MAX_PATH, szFilePath);
	PathRemoveFileSpec(szFilePath); 
	// D:\�ں���\119\FrameWork (6) (2)\Data
	lstrcat(szFilePath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szFilePath;
	if (IDOK == Dlg.DoModal())
	{
		//Dlg.GetPathName()// ���õ� ��θ� ��ȯ���ִ� �Լ� 
		CString wstrFilePath = Dlg.GetPathName(); 
		HANDLE hFile = CreateFile(wstrFilePath.GetString(),GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
			return; 
		DWORD dwByte = 0; 
		DWORD dwStrByte = 0; 
		for (auto& rPair : m_mapUnitInfo)
		{
			dwStrByte = sizeof(wchar_t) * (rPair.second->wstrName.GetLength() + 1); 
			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, rPair.second->wstrName.GetString(), dwStrByte, &dwByte, nullptr); 
			WriteFile(hFile, &rPair.second->iAtt, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->iDef, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->byJob, sizeof(BYTE), &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->byItem, sizeof(BYTE), &dwByte, nullptr);

		}
		CloseHandle(hFile); 
	}
}

//Load
void CUnitTool::OnBnClickedButton5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog Dlg(TRUE,// ���� ���(TRUE) Ȥ�� ���� ���(FALSE) ��� �� ������. 
		L"dat",// ����Ʈ Ȯ���� �� 
		L"*.dat",// ����Ʈ ���� �̸� 
		OFN_OVERWRITEPROMPT);// â�� �⺻ ���¸� �������� �� ����. �ִ� �ߺ����� ����� ���޽��� �����.  
	TCHAR szFilePath[MAX_PATH]{};
	//D:\�ں���\119\FrameWork (6) (2)
	GetCurrentDirectory(MAX_PATH, szFilePath);
	PathRemoveFileSpec(szFilePath);
	// D:\�ں���\119\FrameWork (6) (2)\Data
	lstrcat(szFilePath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szFilePath;
	if (IDOK == Dlg.DoModal())
	{
		//Dlg.GetPathName()// ���õ� ��θ� ��ȯ���ִ� �Լ� 
		CString wstrFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		for (auto& rPair : m_mapUnitInfo)
			Safe_Delete(rPair.second); 
		m_mapUnitInfo.clear();

		m_ListBox.ResetContent();

		DWORD dwByte = 0;
		DWORD dwStrByte = 0;
		wchar_t* pBuf = nullptr; 
		UNITINFO* pUnitData = nullptr; 
		while(true)
		{	
			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

			if (0 == dwByte)
				break; 
			pUnitData = new UNITINFO; 
			pBuf = new wchar_t[dwStrByte]; 
			ReadFile(hFile, pBuf, dwStrByte, &dwByte, nullptr);
			pUnitData->wstrName = pBuf; 
			if (pBuf)
			{
				delete[] pBuf;
				pBuf = nullptr; 
			}

			ReadFile(hFile, &pUnitData->iAtt, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &pUnitData->iDef, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &pUnitData->byJob, sizeof(BYTE), &dwByte, nullptr);
			ReadFile(hFile, &pUnitData->byItem, sizeof(BYTE), &dwByte, nullptr);
			m_mapUnitInfo.emplace(pUnitData->wstrName, pUnitData); 
			m_ListBox.AddString(pUnitData->wstrName); 
		}
		CloseHandle(hFile);
	}
}
