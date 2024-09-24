
// Practice5bView.cpp: CPractice5bView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Practice5b.h"
#endif

#include "Practice5bDoc.h"
#include "Practice5bView.h"
#include "CInputDlg.h";
#include "MainFrm.h";
#include "ChildFrm.h";

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice5bView

IMPLEMENT_DYNCREATE(CPractice5bView, CView)

BEGIN_MESSAGE_MAP(CPractice5bView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CPractice5bView 생성/소멸

CPractice5bView::CPractice5bView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPractice5bView::~CPractice5bView()
{
}

BOOL CPractice5bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPractice5bView 그리기

void CPractice5bView::OnDraw(CDC* pDC)
{
	CPractice5bDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	pDC->TextOut(pDoc->m_nDocX, pDoc->m_nDocY, pDoc->m_strDocText);

}


// CPractice5bView 인쇄

BOOL CPractice5bView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPractice5bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPractice5bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPractice5bView 진단

#ifdef _DEBUG
void CPractice5bView::AssertValid() const
{
	CView::AssertValid();
}

void CPractice5bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice5bDoc* CPractice5bView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice5bDoc)));
	return (CPractice5bDoc*)m_pDocument;
}
#endif //_DEBUG


// CPractice5bView 메시지 처리기


void CPractice5bView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CInputDlg* pInput = new CInputDlg();
	if (pInput->DoModal() == IDOK)
	{
		// 메인 프레임을 가져온다
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		// 현재 활성화된 자식 프레임을 반환
		// MDI로 여러개의 자식 프레임을 열수 있고 각각 독립적으로 상태를 나타냄
		CChildFrame* pChild = (CChildFrame*)pFrame->GetActiveFrame();
		// 자식 프레임에서 활성화된 문서를 가져올 수 있다
		CPractice5bDoc* pDoc = (CPractice5bDoc*)pChild->GetActiveDocument();

		UpdateData(TRUE);

		pDoc->m_nDocX = pInput->m_nX;
		pDoc->m_nDocY = pInput->m_nY;
		pDoc->m_strDocText = pInput->m_strText;

		Invalidate();

	}


	CView::OnRButtonDown(nFlags, point);
}
