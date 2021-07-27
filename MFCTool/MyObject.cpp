#include "stdafx.h"
#include "MyObject.h"
#include "MFCToolView.h"
#include "Texture_Manager.h"

CMyObject::CMyObject()
{
}


CMyObject::~CMyObject()
{
	Release();
}

void CMyObject::Add_Object(const D3DXVECTOR3& vMouse, const D3DXVECTOR3& vSize, const DWORD& dwDrawID)
{
	m_vecObject.emplace_back(new OBJECT(vMouse.x, vMouse.y, vSize.x, vSize.y, dwDrawID));
}

void CMyObject::Save_Objects()
{
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
		HANDLE hFile = CreateFile(wstrFilePath.GetString(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
			return;
		DWORD dwByte = 0;
		DWORD dwStrByte = 0;
		for (auto& rObj : m_vecObject)
		{
			dwStrByte = sizeof(wchar_t) * (rObj->wstrType.GetLength() + 1);
			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, rObj->wstrType.GetString(), dwStrByte, &dwByte, nullptr);
			WriteFile(hFile, &rObj->vPos, sizeof(D3DXVECTOR3), &dwByte, nullptr);
			WriteFile(hFile, &rObj->vSize, sizeof(D3DXVECTOR3), &dwByte, nullptr);
			WriteFile(hFile, &rObj->dwDrawID, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, &rObj->Filepath, sizeof(wstring), &dwByte, nullptr);

		}
		CloseHandle(hFile);
	}
}

void CMyObject::Load_Objects()
{
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

		for (auto& rObj : m_vecObject)
			Safe_Delete(rObj);
		m_vecObject.clear();

		DWORD dwByte = 0;
		DWORD dwStrByte = 0;
		wchar_t* pBuf = nullptr;
		OBJECT* pObjData = nullptr;
		while (true)
		{
			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

			if (0 == dwByte)
				break;
			pObjData = new OBJECT;
			pBuf = new wchar_t[dwStrByte];
			ReadFile(hFile, pBuf, dwStrByte, &dwByte, nullptr);
			pObjData->wstrType = pBuf;
			if (pBuf)
			{
				delete[] pBuf;
				pBuf = nullptr;
			}

			ReadFile(hFile, &pObjData->vPos, sizeof(D3DXVECTOR3), &dwByte, nullptr);
			ReadFile(hFile, &pObjData->vSize, sizeof(D3DXVECTOR3), &dwByte, nullptr);
			ReadFile(hFile, &pObjData->dwDrawID, sizeof(DWORD), &dwByte, nullptr);
			ReadFile(hFile, &pObjData->Filepath, sizeof(wstring), &dwByte, nullptr);
			m_vecObject.emplace_back(pObjData);
		}
		CloseHandle(hFile);
	}
}

HRESULT CMyObject::Ready()
{
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Platform/Desk/Desk0%d.png", L"Terrain", L"Platform", 4)))
		return E_FAIL;
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::SINGLE_TEX, L"../Texture/Platform/Desk/Default.png", L"Default")))
		return E_FAIL;

	return S_OK;
}

void CMyObject::Render()
{
	for (auto& pObj : m_vecObject) {
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"Terrain", L"Platform", pObj->dwDrawID);
		if (nullptr == pTexInfo)
			return;
		float fCenterX = pTexInfo->tImageInfo.Width >> 1;
		float fCenterY = pTexInfo->tImageInfo.Height >> 1;
		D3DXMATRIX matScale, matTrans, matWorld;
		D3DXMatrixScaling(&matScale, pObj->vSize.x, pObj->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, pObj->vPos.x - m_pView->GetScrollPos(SB_HORZ), pObj->vPos.y - m_pView->GetScrollPos(SB_VERT), 0.f);
		matWorld = matScale * matTrans;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CMyObject::Release()
{
	for_each(m_vecObject.begin(), m_vecObject.end(), Safe_Delete<OBJECT*>);
	m_vecObject.clear();
	m_vecObject.shrink_to_fit();
}

CMyObject * CMyObject::Create()
{
	CMyObject* pInstance = new CMyObject;
	if (FAILED(pInstance->Ready()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
