// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool 대화 상자입니다.

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


// CUnitTool 메시지 처리기입니다.


void CUnitTool::OnBnClickedCopy()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	/*
	만약 true를 넣어준다면 
	다이얼로그에서 데이터를 얻어옴. 
	*/
	m_wstrDest = m_wstrSource; 
	m_wstrSource = L"뭐 어쩌라고"; 
	UpdateData(FALSE);
	/*
	만약 false라면 
	데이터를 다이얼로그에게 전달! 
	*/
}


//Add
void CUnitTool::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE); 
	auto& iter_find = m_mapUnitInfo.find(m_wstrName.GetString());
	if (iter_find != m_mapUnitInfo.end())
		return; 

	UNITINFO* pUnitInfo = new UNITINFO{};
	/*ZeroMemory(pUnitInfo, sizeof(UNITINFO)); 안됨*/
	for (int i = 0 ; i < 3; ++i)
	{
		// 현재 버튼이 눌려있는지 아닌지를 판별하는 함수. 
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
		pUnitInfo->byItem |= 검; 
	//0000 0001
	//0000 0010
	//| 0000 0011
	if (m_CheckBox[1].GetCheck())
		pUnitInfo->byItem |= 활; 
	if (m_CheckBox[2].GetCheck())
		pUnitInfo->byItem |= 도; 
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE); 
	for (int i = 0 ; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE); 
		m_CheckBox[i].SetCheck(FALSE);
	}
	// 리스트박스에 현재 선택된 인덱스 번호를 반환 . 
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
	if (iter_find->second->byItem & 검)
		m_CheckBox[0].SetCheck(TRUE); 
	if (iter_find->second->byItem & 활)
		m_CheckBox[1].SetCheck(TRUE); 
	if (iter_find->second->byItem & 도)
		m_CheckBox[2].SetCheck(TRUE); 
	UpdateData(FALSE); 
}

// Delete 
void CUnitTool::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE,// 열기 모드(TRUE) 혹은 저장 모드(FALSE) 어떤것 할 것인지. 
		L"dat",// 디폴트 확장자 명 
		L"*.dat",// 디폴트 파일 이름 
		OFN_OVERWRITEPROMPT);// 창에 기본 상태를 설정해줄 수 있음. 애는 중복파일 저장시 경고메시지 띄워줌.  
	TCHAR szFilePath[MAX_PATH]{}; 
	//D:\박병건\119\FrameWork (6) (2)
	GetCurrentDirectory(MAX_PATH, szFilePath);
	PathRemoveFileSpec(szFilePath); 
	// D:\박병건\119\FrameWork (6) (2)\Data
	lstrcat(szFilePath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szFilePath;
	if (IDOK == Dlg.DoModal())
	{
		//Dlg.GetPathName()// 선택된 경로를 반환해주는 함수 
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(TRUE,// 열기 모드(TRUE) 혹은 저장 모드(FALSE) 어떤것 할 것인지. 
		L"dat",// 디폴트 확장자 명 
		L"*.dat",// 디폴트 파일 이름 
		OFN_OVERWRITEPROMPT);// 창에 기본 상태를 설정해줄 수 있음. 애는 중복파일 저장시 경고메시지 띄워줌.  
	TCHAR szFilePath[MAX_PATH]{};
	//D:\박병건\119\FrameWork (6) (2)
	GetCurrentDirectory(MAX_PATH, szFilePath);
	PathRemoveFileSpec(szFilePath);
	// D:\박병건\119\FrameWork (6) (2)\Data
	lstrcat(szFilePath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szFilePath;
	if (IDOK == Dlg.DoModal())
	{
		//Dlg.GetPathName()// 선택된 경로를 반환해주는 함수 
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
