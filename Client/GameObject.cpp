#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	//:m_tInfo({})
{
// 	INFO* pInfo = new INFO; 
	// °õ°õÈ÷ »ý°¢ÇÏ¸ç ±×¸²±×·ÁºÁ. 
// 	ZeroMemory(pInfo, sizeof(INFO)); 
	// ±×¸² º¸¿©Áà ? 
// 	ZeroMemory(&pInfo, sizeof(INFO));
	ZeroMemory(&m_tInfo, sizeof(INFO)); 
}


CGameObject::~CGameObject()
{
}
