#pragma once
class CTexture abstract
{
public:
	explicit CTexture();
	virtual ~CTexture();
public:
	virtual HRESULT Insert_Texture(const wstring& wstrFilePath,
		const wstring& wstrStateKey = L"",
		const DWORD dwCount = 0)PURE; 
	virtual const TEXINFO* Get_TexInfo_Texture(const wstring& wstrStateKey = L"",
		const DWORD& dwIndex =0 )PURE; 
	virtual void Release_Texture()PURE; 

	//singleTexture, MultiTexture 
	// ObjectKey -> StateKey ->그림 여러장. 


};

