#include "stdafx.h"
#include "Terrain.h"
#include "MFCToolView.h"


CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release_Terrain(); 
}

void CTerrain::Tile_Change(const D3DXVECTOR3 & vMouse, const DWORD & dwDrawID, const DWORD & dwOption /*= 0*/)
{
	int iIndex = GetTileIndex(vMouse); 

	if (-1 == iIndex)
		return; 

	m_vecTile[iIndex]->dwDrawID = dwDrawID; 
	m_vecTile[iIndex]->dwOption = dwOption; 
}

int CTerrain::GetTileIndex(const D3DXVECTOR3 & vPos)
{
	for (int i = 0 ; i < m_vecTile.size(); ++i)
	{
		if (IsPicking(vPos, i))
			return i;
	}
	return -1;
}

bool CTerrain::IsPicking(const D3DXVECTOR3 & vPos, const int & iIndex)//mouse, vector index
{
	D3DXVECTOR3 vPoint[4] = {
		{ m_vecTile[iIndex]->vPos.x + (TILECX>> 1), m_vecTile[iIndex]->vPos.y + (TILECY >> 1), 0.f },//오른쪽 아래
		{ m_vecTile[iIndex]->vPos.x + (TILECX >> 1), m_vecTile[iIndex]->vPos.y - (TILECY >> 1), 0.f },//오른쪽 위
		{ m_vecTile[iIndex]->vPos.x - (TILECX>>1), m_vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f },//왼쪽 위
		{ m_vecTile[iIndex]->vPos.x - (TILECX >> 1), m_vecTile[iIndex]->vPos.y + (TILECY >> 1), 0.f }//왼쪽 아래
	};

	if (vPos.x < vPoint[0].x && vPos.x < vPoint[1].x &&
		vPos.x > vPoint[2].x && vPos.x > vPoint[3].x &&
		vPos.y < vPoint[0].y && vPos.y < vPoint[3].y &&
		vPos.y > vPoint[1].y && vPos.y > vPoint[2].y)
		return true;

	return false;
}

HRESULT CTerrain::Ready_Terrain()
{
	float fX = 0.f, fY = 0.f; 
	TILE* pTile = nullptr; 
	m_vecTile.reserve(TILEX * TILEY); 
	for (int i = 0 ; i < TILEY ; ++i)
	{
		for (int j = 0 ;  j < TILEX ; ++j)
		{
			pTile = new TILE; 
			fX = (j * TILECX) + (TILECY >> 1);
			fY = i * TILECY + (TILECX >> 1);
			pTile->vPos = D3DXVECTOR3(fX, fY, 0.f); 
			pTile->vSize = { 1.f, 1.f, 0.f }; 
			pTile->dwDrawID = 0; 
			pTile->dwOption = 0;
			m_vecTile.emplace_back(pTile); 
		}
	}
	return S_OK;
}

void CTerrain::Render_Terrain()
{
	TCHAR szBuf[MAX_PATH]{}; 
	for (int i = 0 ; i < TILEY ; ++i)
	{
		for (int j = 0 ; j < TILEX ; ++j)
		{
			int iIndex = j + (i * TILEX);
			if (0 > iIndex || m_vecTile.size() <= iIndex)
				return; 
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"Terrain", L"Platform", m_vecTile[iIndex]->dwDrawID); 
			if (nullptr == pTexInfo)
				return; 
			float fCenterX = pTexInfo->tImageInfo.Width >> 1; 
			float fCenterY = pTexInfo->tImageInfo.Height >> 1; 
			D3DXMATRIX matScale, matTrans, matWorld; 
			D3DXMatrixScaling(&matScale, m_vecTile[iIndex]->vSize.x, m_vecTile[iIndex]->vSize.y, 0.f); 
			D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->vPos.x - m_pView->GetScrollPos(SB_HORZ), m_vecTile[iIndex]->vPos.y - m_pView->GetScrollPos(SB_VERT), 0.f);
			matWorld = matScale * matTrans; 
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255)); 
		}
	}

}

void CTerrain::Mini_Render_Terrain()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			int iIndex = j + (i * TILEX);
			if (0 > iIndex || m_vecTile.size() <= iIndex)
				return;
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"Terrain", L"Platform", m_vecTile[iIndex]->dwDrawID);
			if (nullptr == pTexInfo)
				return;
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			D3DXMATRIX matScale, matTrans, matWorld, matRatio;
			D3DXMatrixScaling(&matRatio, 0.3f, 0.3f, 0.f);
			D3DXMatrixScaling(&matScale, m_vecTile[iIndex]->vSize.x, m_vecTile[iIndex]->vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->vPos.x - m_pView->GetScrollPos(SB_HORZ), m_vecTile[iIndex]->vPos.y - m_pView->GetScrollPos(SB_VERT), 0.f);
			matWorld = matScale * matTrans;
			matWorld *= matRatio;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CTerrain::Release_Terrain()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>);
	m_vecTile.clear(); 
	m_vecTile.shrink_to_fit(); 
}

CTerrain * CTerrain::Create()
{
	CTerrain* pInstance = new CTerrain; 
	if (FAILED(pInstance->Ready_Terrain()))
	{
		Safe_Delete(pInstance); 
		return nullptr;
	}
	return pInstance;
}
