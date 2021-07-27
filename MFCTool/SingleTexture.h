#pragma once
#include "Texture.h"
class CSingleTexture final :
	public CTexture
{
public:
	explicit CSingleTexture();
	virtual ~CSingleTexture();
public:
	// CTexture을(를) 통해 상속됨
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const DWORD dwCount = 0) override;
	virtual const TEXINFO * Get_TexInfo_Texture(const wstring & wstrStateKey = L"", const DWORD & dwIndex = 0) override;
	virtual void Release_Texture()override;
private:
	TEXINFO m_tTexInfo; 
};

