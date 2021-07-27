#include "stdafx.h"
#include "SingleTexture.h"


CSingleTexture::CSingleTexture()
	:m_tTexInfo({})
{
}


CSingleTexture::~CSingleTexture()
{
	Release_Texture(); 
}

HRESULT CSingleTexture::Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey /*= L""*/, const DWORD dwCount /*= 0*/)
{
	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_tTexInfo.tImageInfo)))
		return E_FAIL;
	;
	// MipLevels - 여러가지 크기로 이미지를 준비해 두는 것을 뜻한다. 
	// 왜 ? 이미지를 축소하거나 확대하는 작업은 생각보다 큰 부하를 가져오기 때문에 
	// 상황에 맞는 크기의 이미지를 가져다 쓰면 처리속도가 빨라지기 때문 .
	// 대신 있을 수도 있고 없을 수도 있다. 

	// 이미지를 어디에 저장할 것인지를 뜻한다. 
	//D3DPOOL_MANAGED - 기본 gPU에 데이터를 보관하고 모지라면 rAm까지 가져다 쓰게싿. 
	//D3DPOOL_DEFAULT - GPU만 사용하겠다 - 만약 GPU에 메모리 공간이 부족하다면 더이상 데이터를 담지 못함. 
	//빠르지만 데이터 손실날 확률 높음. 
	//D3DPOOL_SYSTEMMEM - 메인메모리에 데이터를 담겠다. 안정적이지만 느리다. 
	if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Device::Get_Instance()->Get_Device(),
		wstrFilePath.c_str(),
		m_tTexInfo.tImageInfo.Width,
		m_tTexInfo.tImageInfo.Height,
		m_tTexInfo.tImageInfo.MipLevels,
		0,
		m_tTexInfo.tImageInfo.Format,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr,
		&m_tTexInfo.pTexture)))
		return E_FAIL; 

	return S_OK;
}

const TEXINFO * CSingleTexture::Get_TexInfo_Texture(const wstring & wstrStateKey /*= L""*/, const DWORD & dwIndex /*= 0*/)
{
	return &m_tTexInfo;
}

void CSingleTexture::Release_Texture()
{
	if (m_tTexInfo.pTexture)
		m_tTexInfo.pTexture->Release();
}

