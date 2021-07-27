#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vSize;
	//D3DXVECTOR2; 
	//D3DXVECTOR4; //x,y,z,w
}INFO;

typedef struct tagTexInfo
{
	LPDIRECT3DTEXTURE9 pTexture; // 너네가 API떄 사용했던 HBITMAP
	D3DXIMAGE_INFO tImageInfo; // 
}TEXINFO;
typedef struct tagTile
{
	D3DXVECTOR3 vPos; 
	D3DXVECTOR3 vSize; 
	DWORD dwDrawID; 
	DWORD dwOption;
}TILE;

typedef struct tagUnitInfo
{
#ifdef _AFX
	CString wstrName; 
#else 
	wstring wstrName; 
#endif // _AFX

	int iAtt; 
	int iDef;
	BYTE byJob; 
	BYTE byItem; 
}UNITINFO;

typedef struct tagObject {
#ifdef _AFX
	CString wstrType;
#else 
	wstring wstrType;
#endif // _AFX
	tagObject() {}
	tagObject(float _x, float _y) {
		vPos.x = _x;
		vPos.y = _y;
	}
	tagObject(float _x, float _y, float _sx, float _sy, DWORD _dID) {
		vPos.x = _x;
		vPos.y = _y;
		vSize.x = _sx;
		vSize.y = _sy;
		dwDrawID = _dID;
	}
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	DWORD dwDrawID;
	wstring Filepath;
}OBJECT;