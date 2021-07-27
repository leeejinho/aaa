#pragma once
//0000 0001
#define °Ë 0x01
//0000 0010
#define È° 0x02
//0000 0100
#define µµ 0x04
#define OBJ_NOEVENT 0
#define OBJ_DEAD 1
#ifdef _AFX
#define ERR_MSG(message)					\
AfxMessageBox(message);
#else
#define ERR_MSG(message)					\
MessageBox(nullptr, message, L"System Error", MB_OK);

#endif // _AFX

#define DECLARE_SINGLETON(className)						\
public:														\
static className* Get_Instance()							\
{															\
	if (!m_pInstance)										\
		m_pInstance = new className;						\
	return m_pInstance;										\
}															\
static void Destroy_Instance()								\
{															\
	if (m_pInstance)										\
	{														\
		delete m_pInstance;									\
		m_pInstance = nullptr;								\
	}														\
}															\
private:													\
	static className* m_pInstance;							
#define IMPLEMENT_SINGLETON(ClassName)						\
ClassName* ClassName::m_pInstance = nullptr; 