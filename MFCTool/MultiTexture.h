#pragma once
#include "Texture.h"
class CMultiTexture final :
	public CTexture
{
public:
	CMultiTexture();
	virtual ~CMultiTexture();
public:
	// CTexture��(��) ���� ��ӵ�
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey , const DWORD dwCount ) override;
	virtual const TEXINFO * Get_TexInfo_Texture(const wstring & wstrStateKey , const DWORD & dwIndex ) override;
	virtual void Release_Texture() override;
private:
	// ���⿡���� Ű���� ?? stateKey 
	map<wstring, vector<TEXINFO*>> m_mapMultiTexture; 
};

