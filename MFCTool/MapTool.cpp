// MapTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "Texture_Manager.h"
#include "MainFrm.h"
#include "MFCToolView.h"
#include "Terrain.h"
#include "WallMgr.h"
#include "Wall.h"
#include "LineMgr.h"
#include "Line.h"

// CMapTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
	, m_dwDrawID(0)
{

}

CMapTool::~CMapTool()
{
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnLbnSelchangePicture)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CMapTool::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMapTool::OnBnClickedRemove)
END_MESSAGE_MAP()


// CMapTool �޽��� ó�����Դϴ�.
void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int iCount = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);//���ϰ���
	TCHAR szFilePath[MAX_PATH]{}; 

	for (int i = 0 ; i < iCount ; ++i)
	{
		//���ϰ�θ� ����
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH); 
		CString wstrRelativePath = CFileInfo::ConvertRelativePath(szFilePath); 
		CString wstrFileNameAndEx = PathFindFileName(szFilePath); 
		TCHAR szFileName[MAX_PATH]{}; 
		lstrcpy(szFileName, wstrFileNameAndEx.GetString()); 
		PathRemoveExtension(szFileName);
		m_ListBox.AddString(szFileName);
		CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::SINGLE_TEX, wstrRelativePath.GetString(), szFileName);
	}
	m_ListBox.SetHorizontalExtent(800);
	UpdateData(FALSE); 
	CDialog::OnDropFiles(hDropInfo);
}


void CMapTool::OnLbnSelchangePicture()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE); 
	int iIndex = m_ListBox.GetCurSel(); 

	CString wstrFileName; 
	m_ListBox.GetText(iIndex, wstrFileName);

	//int i = 0; 
	//for (; i < wstrFileName.GetLength() ; ++i)
	//{
	//	//isdigit - 0~ 9������ �������� �Ǻ����ִ� �Լ�. 
	//	if (isdigit(wstrFileName[i]))
	//		break; 
	//}
	//// 15 
	//wstrFileName.Delete(0, i); // Tile 
	//m_dwDrawID = _ttoi(wstrFileName.GetString());
	m_pObjectKey = wstrFileName;

	CGraphic_Device::Get_Instance()->Render_Begin(); 
	
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture((TCHAR*)(LPCTSTR)m_pObjectKey);
	if (nullptr == pTexInfo)
		return;

	D3DXMATRIX matScale, matTrans, matWorld; 
	D3DXMatrixScaling(&matScale, WINCX / float(pTexInfo->tImageInfo.Width), WINCY / float(pTexInfo->tImageInfo.Height), 0.f);
	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f); 
	matWorld = matScale * matTrans; 
	
	float fCenterX = pTexInfo->tImageInfo.Width >> 1; 
	float fCenterY = pTexInfo->tImageInfo.Height >> 1; 

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld); 
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255)); 
	CGraphic_Device::Get_Instance()->Render_End(m_Picture.m_hWnd);
	UpdateData(FALSE);
}

//Save
void CMapTool::OnBnClickedButton1()
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
		CString wstrFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD dwByte = 0;
		if(m_Radio[0].GetCheck())
		{
			list<CLine*>& listLine = CLineMgr::Get_Instance()->Get_List();
			for (auto& pLine : listLine)
			{
				WriteFile(hFile, pLine->Get_LinePos(0), sizeof(D3DXVECTOR2), &dwByte, nullptr);
				WriteFile(hFile, pLine->Get_LinePos(1), sizeof(D3DXVECTOR2), &dwByte, nullptr);
			}
		}
		else if(m_Radio[1].GetCheck())
		{
			list<CWall*>& listWall = CWallMgr::Get_Instance()->Get_List();
			for (auto& pLine : listWall)
			{
				WriteFile(hFile, pLine->Get_RectPos(0), sizeof(D3DXVECTOR2), &dwByte, nullptr);
				WriteFile(hFile, pLine->Get_RectPos(2), sizeof(D3DXVECTOR2), &dwByte, nullptr);
			}
		}

		CloseHandle(hFile); 
	}
}

//Load
void CMapTool::OnBnClickedButton6()
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
		CString wstrFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
			return;
		
		//CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		//CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_tMainSplitter.GetPane(0, 1));

		if (m_Radio[0].GetCheck())
			CLineMgr::Get_Instance()->Release_Line();
		else if (m_Radio[1].GetCheck())
			CWallMgr::Get_Instance()->Release_Wall();
		DWORD dwByte = 0;
		D3DXVECTOR2 vTemp[2] = {};
		TILE* pTile = nullptr; 
		while (true)
		{						
			ReadFile(hFile, vTemp[0], sizeof(D3DXVECTOR2), &dwByte, nullptr);
			ReadFile(hFile, vTemp[1], sizeof(D3DXVECTOR2), &dwByte, nullptr);
			
			if (0 == dwByte)
				break;

			if (m_Radio[0].GetCheck())
				CLineMgr::Get_Instance()->Add_Line(new CLine(vTemp[0], vTemp[1]));
			else if (m_Radio[1].GetCheck())
				CWallMgr::Get_Instance()->Add_Wall(CWall::Create(vTemp[0], vTemp[1]));			
		}

		//pView->Invalidate(TRUE);
		CloseHandle(hFile);
	}
}


void CMapTool::OnBnClickedRemove()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_Radio[0].GetCheck())
	{
		CLineMgr::Get_Instance()->Pop_Back();
	}
	else if (m_Radio[1].GetCheck())
	{
		CWallMgr::Get_Instance()->Pop_Back();
	}
}
