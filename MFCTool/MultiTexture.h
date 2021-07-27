#pragma once
#include "Texture.h"
class CMultiTexture final :
	public CTexture
{
public:
	CMultiTexture();
	virtual ~CMultiTexture();
public:
	// CTexture을(를) 통해 상속됨
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey , const DWORD dwCount ) override;
	virtual const TEXINFO * Get_TexInfo_Texture(const wstring & wstrStateKey , const DWORD & dwIndex ) override;
	virtual void Release_Texture() override;
private:
	// 여기에서의 키값은 ?? stateKey 
	map<wstring, vector<TEXINFO*>> m_mapMultiTexture; 
};

