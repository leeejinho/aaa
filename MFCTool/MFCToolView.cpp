
// MFCToolView.cpp : CMFCToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCTool.h"
#endif

#include "MFCToolDoc.h"
#include "MFCToolView.h"
#include "Terrain.h"
#include "MainFrm.h"
#include "MiniView.h"
#include "Form.h"
#include "MapTool.h"
#include "MyObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
HWND g_hWND; 

// CMFCToolView

IMPLEMENT_DYNCREATE(CMFCToolView, CScrollView)

BEGIN_MESSAGE_MAP(CMFCToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCToolView 생성/소멸

CMFCToolView::CMFCToolView()
	:m_pTerrain(nullptr), m_pMyObject(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_fAngle = 0; 
	m_iDrawID = 0; 
	m_iMaxDrawID = 10; 
}

CMFCToolView::~CMFCToolView()
{
	//m_pTerrain->Release_Terrain(); 
	CTexture_Manager::Destroy_Instance();
	CGraphic_Device::Destroy_Instance(); 
}

BOOL CMFCToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCToolView 그리기

void CMFCToolView::OnDraw(CDC* /*pDC*/)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CGraphic_Device::Get_Instance()->Render_Begin();

	//m_pTerrain->Render_Terrain(); 
	m_pMyObject->Render();
	CGraphic_Device::Get_Instance()->Render_End();

 //	m_fAngle += 5.f; 
 //	++m_iDrawID;
 //	if (m_iDrawID > m_iMaxDrawID)
 //	{
 //		m_iDrawID = 0; 
 //	}

	//CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	//CForm* pForm = dynamic_cast<CForm*>(pMainFrame->m_tSecondSplitter.GetPane(1, 0));
	//TCHAR* pObjectKey = (TCHAR*)(LPCTSTR)(pForm->m_tMapTool.m_pObjectKey);
	//	
 //	CGraphic_Device::Get_Instance()->Render_Begin();
 // 	
	//const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo_Texture(pObjectKey);
	//if (pTexInfo != nullptr)
	//{
	//	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
	//	// 이미지 반전 개꿀. 
	//	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	//	//D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	//	D3DXMatrixTranslation(&matTrans, -GetScrollPos(SB_HORZ), -GetScrollPos(SB_VERT), 0.f);
	//	matWorld = matScale * /*matRotZ * */matTrans;

	//	float fCenterX = pTexInfo->tImageInfo.Width >> 1;
	//	float fCenterY = pTexInfo->tImageInfo.Height >> 1;
	//	RECT rc{ 0, 0, 400, 300 };
	//	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	//	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, nullptr/*&D3DXVECTOR3(fCenterX, fCenterY, 0.f)*/, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	//}
 //	CGraphic_Device::Get_Instance()->Render_End(); 
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
// 	pDC->Rectangle(100, 100, 200, 200); 
// 	pDC->Ellipse(100, 100, 200, 200); 
}


// CMFCToolView 인쇄

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCToolView 진단

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	
	CScrollView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView 메시지 처리기


void CMFCToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	g_hWND = m_hWnd; 
	// 이거 스크롤 적용 대상은 DC로 그림그리는 것들 대상. 
	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, (TILECY >> 1)* TILEY));
	// 윈도우 창 크기 재조정. 
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	RECT rcMain{}; 
	pMain->GetWindowRect(&rcMain); 
	rcMain.right = rcMain.right - rcMain.left; //1640 - 100 1540
	rcMain.bottom = rcMain.bottom - rcMain.top; 
	rcMain.left = 0; 
	rcMain.top = 0; 
	//.......................................................................
	RECT rcView{}; 
	GetClientRect(&rcView);

	int iGapX = rcMain.right - rcView.right; 
	int iGapY = rcMain.bottom - rcView.bottom; 

	pMain->SetWindowPos(nullptr, 0, 0, WINCX + iGapX + 1, WINCY + iGapY + 1, SWP_NOMOVE); 

	if (FAILED(CGraphic_Device::Get_Instance()->Ready_Graphic_Device()))
		return; 
	//L"../Texture/Stage/Terrain/Tile/Tile%d.png";
	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX,L"../Texture/Stage/Terrain/Tile/Tile%d.png", L"Terrain", L"Tile", 36)))
	//	return; 
	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Player/Attack/AKIHA_AKI01_00%d.png", L"Player", L"Attack", 6)))
	//	return;
	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Player/Dash/AKIHA_AKI13_00%d.png", L"Player", L"Dash", 11)))
	//	return;
	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::SINGLE_TEX, L"../Texture/Stage/Player/Dash/AKIHA_AKI13_00%d.png", L"Player", L"Dash", 11)))
	//	return;

	/*m_pTerrain = CTerrain::Create(); 
	if (nullptr == m_pTerrain)
		return; 
	m_pTerrain->Set_View(this); */
	m_pMyObject = CMyObject::Create();
	if (nullptr == m_pMyObject)
		return;
	m_pMyObject->Set_View(this);
	CObjectTool::Set_MyObject(m_pMyObject);
}


void CMFCToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	TCHAR szBuf[MAX_PATH]{}; 
 	// 문자열 대상 출력하는 함수. 
 	//swprintf_s(szBuf, L"X : %d, Y : %d", point.x, point.y);
 
 	//ERR_MSG(szBuf); 
	D3DXVECTOR3 vMouse{ float(point.x) + GetScrollPos(SB_HORZ), float(point.y) + GetScrollPos(SB_VERT), 0.f };
	
	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CForm* pForm = dynamic_cast<CForm*>(pMainFrame->m_tSecondSplitter.GetPane(1, 0)); 
	DWORD dwDrawID = pForm->m_tObjectTool.m_dwDrawID;

	m_pMyObject->Set_PosX(vMouse.x);
	m_pMyObject->Set_PosY(vMouse.y);

	Invalidate(FALSE); 
	
	/*CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMainFrame->m_tSecondSplitter.GetPane(0, 0));
	pMiniView->Invalidate(FALSE); */

	CScrollView::OnLButtonDown(nFlags, point);
}
