#pragma once
class CMFCToolView; 
class CTerrain final
{
private:
	CTerrain();
public:
	~CTerrain();
public:
	vector<TILE*>& Get_TileData() { return m_vecTile; }
public:
	void Set_View(CMFCToolView* pView) { m_pView = pView;  }
public:
	void Tile_Change(const D3DXVECTOR3& vMouse, const DWORD& dwDrawID, const DWORD& dwOption = 0);
	int		GetTileIndex(const D3DXVECTOR3& vPos); 
	bool	IsPicking(const D3DXVECTOR3& vPos, const int& iIndex); 
public:
	HRESULT Ready_Terrain(); 
	void	Render_Terrain(); 
	void	Mini_Render_Terrain(); 
	void	Release_Terrain(); 
public:
	static CTerrain* Create(); 
private:
	vector<TILE*> m_vecTile; 
	CMFCToolView* m_pView; 
};

