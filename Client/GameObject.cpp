#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	//:m_tInfo({})
{
// 	INFO* pInfo = new INFO; 
	// ������ �����ϸ� �׸��׷���. 
// 	ZeroMemory(pInfo, sizeof(INFO)); 
	// �׸� ������ ? 
// 	ZeroMemory(&pInfo, sizeof(INFO));
	ZeroMemory(&m_tInfo, sizeof(INFO)); 
}


CGameObject::~CGameObject()
{
}
