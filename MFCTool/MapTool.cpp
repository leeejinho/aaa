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
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnLbnSelchangePicture)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CMapTool::OnBnClickedButton6)
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
		CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd()); 
		CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_tMainSplitter.GetPane(0, 1)); 
		const vector<TILE*>& vecTileData = pView->m_pTerrain->Get_TileData();
		for (auto& pTile : vecTileData)
			WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

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


		CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_tMainSplitter.GetPane(0, 1));
		vector<TILE*>& vecTileData = pView->m_pTerrain->Get_TileData();
		for (auto& pTile : vecTileData)
			Safe_Delete(pTile); 
		// �̸� ���ϴµ� �̵������� ���� �� ���� ���� ���. 
		//����ȭ �ı��Ѵ�!! ����? 
		vecTileData.clear(); 
		DWORD dwByte = 0;
		TILE* pTile = nullptr; 
		while (true)
		{
			pTile = new TILE; 
			ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr); 
			if (0 == dwByte)
				break; 
			vecTileData.emplace_back(pTile); 
		}
		pView->Invalidate(TRUE); 
		CloseHandle(hFile);
	}
}
