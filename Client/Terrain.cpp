#include "stdafx.h"
#include "Terrain.h"



CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release_GameObject(); 
}

CTerrain * CTerrain::Create()
{
	CTerrain* pInstance = new CTerrain; 
	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance); 
		return nullptr;
	}
	return pInstance;
}

HRESULT CTerrain::Ready_GameObject()
{
	float fX = 0.f, fY = 0.f;
	TILE* pTile = nullptr;
	m_vecTile.reserve(TILEX * TILEY);
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			pTile = new TILE;
			fX = (j * TILECX) + ((i % 2) * (TILECX >> 1));
			fY = i * (TILECY >> 1);
			pTile->vPos = D3DXVECTOR3(fX, fY, 0.f);
			pTile->vSize = { 1.f, 1.f, 0.f };
			pTile->dwDrawID = 4;
			pTile->dwOption = 0;
			m_vecTile.emplace_back(pTile);
		}
	}
	return S_OK;
}

int CTerrain::Update_GameObject()
{
	return 0;
}

void CTerrain::Late_Update_GameObject()
{
}

void CTerrain::Render_GameObject()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			int iIndex = j + (i * TILEX);
			if (0 > iIndex || m_vecTile.size() <= iIndex)
				return;
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(L"Terrain", L"Tile", m_vecTile[iIndex]->dwDrawID);
			if (nullptr == pTexInfo)
				return;
			float fCenterX = pTexInfo->tImageInfo.Width >> 1;
			float fCenterY = pTexInfo->tImageInfo.Height >> 1;
			D3DXMATRIX matScale, matTrans, matWorld;
			D3DXMatrixScaling(&matScale, m_vecTile[iIndex]->vSize.x, m_vecTile[iIndex]->vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y, 0.f);
			matWorld = matScale * matTrans;
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CTerrain::Release_GameObject()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}
