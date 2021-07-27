// ObjectTool.cpp : implementation file
//

#include "stdafx.h"
#include "MFCTool.h"
#include "ObjectTool.h"
#include "FileInfo.h"
#include "afxdialogex.h"
#include "MyObject.h"

// CObjectTool dialog

IMPLEMENT_DYNAMIC(CObjectTool, CDialog)
CMyObject* CObjectTool::m_pMyObject = nullptr;
CObjectTool::CObjectTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OBJECTTOOL, pParent)
	, m_wstrType(_T(""))
	, m_wstrPointX(_T(""))
	, m_wstrPointY(_T(""))
{
	//
}

CObjectTool::~CObjectTool()
{
	for (auto& rPair : m_mapObjInfo)
		Safe_Delete(rPair.second);
	m_mapObjInfo.clear();
}

void CObjectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE2, m_Picture);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO4, m_Radio[2]);
	DDX_Control(pDX, IDC_LIST2, m_ObjListBox);
	DDX_Text(pDX, IDC_EDIT5, m_wstrPointX);
	DDX_Text(pDX, IDC_EDIT4, m_wstrPointY);
}

BEGIN_MESSAGE_MAP(CObjectTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CObjectTool::OnLbnSelchangePicture)
	ON_BN_CLICKED(IDC_BUTTON1, &CObjectTool::OnBnClickedButton1)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST2, &CObjectTool::OnLbnSelchangePicture2)
	//ON_BN_CLICKED(IDC_BUTTON7, &CObjectTool::OnBnClickedAddObj)
	ON_BN_CLICKED(IDC_BUTTON9, &CObjectTool::OnBnClickedRefresh)
	ON_BN_CLICKED(IDC_BUTTON6, &CObjectTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON8, &CObjectTool::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CObjectTool message handlers
//WM_DROPFILE

void CObjectTool::OnLbnSelchangePicture()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iIndex = m_ListBox.GetCurSel();

	CString wstrFileName;
	m_ListBox.GetText(iIndex, wstrFileName);

	int i = 0;
	for (; i < wstrFileName.GetLength(); ++i)
	{
		//isdigit - 0~ 9까지의 숫자인지 판별해주는 함수. 
		if (isdigit(wstrFileName[i]))
			break;
	}
	wstrFileName.Delete(0, i); // Desk
	m_dwDrawID = _ttoi(wstrFileName.GetString());

	CGraphic_Device::Get_Instance()->Render_Begin();

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture((TCHAR*)(LPCTSTR)wstrFileName);
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

//add
void CObjectTool::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	auto& iter_find = m_mapObjInfo.find(m_wstrType.GetString());
	if (iter_find != m_mapObjInfo.end())
		return;

	int iIndex = m_ListBox.GetCurSel();
	CString wstrFileName;
	m_ListBox.GetText(iIndex, wstrFileName);

	OBJECT* pObjInfo = new OBJECT();
	pObjInfo->vPos = { m_pMyObject->Get_PosX(), m_pMyObject->Get_PosY(), 0.f };
	pObjInfo->vSize = { 1.f, 1.f, 0.f };
	pObjInfo->Filepath = m_vecFilePath[iIndex];
	pObjInfo->dwDrawID = iIndex;

	if (m_Radio[0].GetCheck())
		pObjInfo->wstrType = L"Platform";
	else if (m_Radio[1].GetCheck())
		pObjInfo->wstrType = L"Monster";
	else if(m_Radio[2].GetCheck())
		pObjInfo->wstrType = L"Weapon";

	m_pMyObject->Get_ObjData().emplace_back(pObjInfo);

	m_ObjListBox.AddString(pObjInfo->wstrType);//
	UpdateData(FALSE);
}


void CObjectTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default
	int iCount = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);//파일개수
	TCHAR szFilePath[MAX_PATH]{};

	for (int i = 0; i < iCount; ++i)
	{
		//파일경로명 단축
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);
		CString wstrRelativePath = CFileInfo::ConvertRelativePath(szFilePath);
		CString wstrFileNameAndEx = PathFindFileName(szFilePath);
		TCHAR szFileName[MAX_PATH]{};
		lstrcpy(szFileName, wstrFileNameAndEx.GetString());
		PathRemoveExtension(szFileName);
		m_ListBox.AddString(szFileName);
		CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::SINGLE_TEX, wstrRelativePath.GetString(), szFileName);
		m_vecFilePath.emplace_back(wstrRelativePath.GetString());
	}
	m_ListBox.SetHorizontalExtent(800);
	UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);	
}

void CObjectTool::OnLbnSelchangePicture2()
{
	UpdateData(TRUE);
	int iIndex = m_ListBox.GetCurSel();

	CString wstrFileName;
	m_ListBox.GetText(iIndex, wstrFileName);

	//wstrFileName.Delete(0, i); // Tile 
	//m_dwDrawID = _ttoi(wstrFileName.GetString());

	CGraphic_Device::Get_Instance()->Render_Begin();

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture((TCHAR*)(LPCTSTR)wstrFileName);
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

void CObjectTool::OnBnClickedRefresh()
{
	UpdateData(TRUE);
	CString str;
	str.Format(_T("%f"), m_pMyObject->Get_PosX());
	m_wstrPointX = str;
	str.Format(_T("%f"), m_pMyObject->Get_PosY());
	m_wstrPointY = str;
	UpdateData(FALSE);
}


void CObjectTool::OnBnClickedSave()
{
	m_pMyObject->Save_Objects();
}


void CObjectTool::OnBnClickedButtonLoad()
{
	m_pMyObject->Load_Objects();
}
