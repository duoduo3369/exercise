// PlaneView.cpp : CPlaneView 类的实现
//

#include "stdafx.h"
#include "public.h"
#include <cmath>
//#include "GameObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



RECT GetLastRect(CPlaneDoc* pDoc);

// CPlaneView

IMPLEMENT_DYNCREATE(CPlaneView, CView)

BEGIN_MESSAGE_MAP(CPlaneView, CView)
//    ON_WM_LBUTTONDOWN()
//    ON_WM_RBUTTONDOWN()
//    ON_WM_KEYDOWN()
//    ON_WM_TIMER()
//    ON_WM_DESTROY()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CPlaneView 构造/析构

CPlaneView::CPlaneView()
{
	// TODO: 在此处添加构造代码

}

CPlaneView::~CPlaneView()
{
}

BOOL CPlaneView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneView 绘制

void CPlaneView::OnDraw(CDC* pDC)
{
	CPlaneDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
    for(vector<CEnemy>::iterator it = pDoc->enemyArray.begin(); it != pDoc->enemyArray.end(); ++it)
    {
        
        it->Draw(pDC,FALSE);
    }

    pDoc->myPlane.Draw(pDC,FALSE);
    
}


// CPlaneView 诊断

#ifdef _DEBUG
void CPlaneView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneDoc* CPlaneView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneDoc)));
	return (CPlaneDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneView 消息处理程序

//void CPlaneView::OnLButtonDown(UINT nFlags, CPoint point)
//{
//    CPlaneDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//    pDoc->pointArray.push_back(point);    
//    this->Invalidate();
//    CView::OnLButtonDown(nFlags, point);
//}


//void CPlaneView::OnRButtonDown(UINT nFlags, CPoint point)
//{
//    CPlaneDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//    if(!pDoc->pointArray.empty())
//    {
//        pDoc->pointArray.pop_back();
//    }
//    this->Invalidate();
//    CView::OnLButtonDown(nFlags, point);
//}

//void CPlaneView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//    CPlaneDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//    if(!pDoc->pointArray.empty())
//    {
//        RECT lastRect = GetLastRect(pDoc);
//        int lastRectIndex = pDoc->pointArray.size()-1;
//        double leftrightGap = 3.2 * 3;
//        double updownGap = 2.4 * 3;
//        
//        switch(nChar)
//        {
//            case VK_LEFT:
//                pDoc->pointArray[lastRectIndex].x -= leftrightGap;
//                break;
//            case VK_RIGHT:
//                pDoc->pointArray[lastRectIndex].x += leftrightGap;
//                break;
//            case VK_UP:
//                pDoc->pointArray[lastRectIndex].y -= updownGap;
//                break;
//            case VK_DOWN:
//                pDoc->pointArray[lastRectIndex].y += updownGap;
//                break;
//
//        }
//        
//        this->InvalidateRect(&lastRect);
//        
//    }
//    
//    CView::OnKeyDown(nChar, nRepCnt, nFlags);
//}

//void CPlaneView::OnInitialUpdate()
//{
//    SetTimer(TIMER_10,10,0); 
//    CView::OnInitialUpdate();
//
//    // TODO: 在此添加专用代码和/或调用基类
//}


//void CPlaneView::OnTimer(UINT_PTR nIDEvent)
//{
//    CPlaneDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//    if(!pDoc->pointArray.empty())
//    {
//
//        RECT lastRect = GetLastRect(pDoc);
//        int lastRectIndex = pDoc->pointArray.size()-1;
//        double leftrightGap = 3.2 * 3;
//        double updownGap = 2.4 * 3;
//        if(pDoc->pointArray[lastRectIndex].x > 0)
//        {
//            leftrightGap = fabs(leftrightGap);
//        }
//        else
//        {
//            leftrightGap = -fabs(leftrightGap);
//        }
//        if(pDoc->pointArray[lastRectIndex].y > 0)
//        {
//            updownGap = fabs(updownGap);            
//        }
//        else
//        {
//            updownGap = -fabs(updownGap);    
//        }
//
//        pDoc->pointArray[lastRectIndex].x -= leftrightGap;
//        pDoc->pointArray[lastRectIndex].y -= updownGap;
//        this->InvalidateRect(&lastRect);
//    }    
//    
//    CView::OnTimer(nIDEvent);
//}

//void CPlaneView::OnDestroy()
//{
//    KillTimer(TIMER_10);
//    CView::OnDestroy();
//
//    // TODO: 在此处添加消息处理程序代码
//}


void CPlaneView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CPlaneDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
    {
        return;
    }
    CEnemy enemy(point);
    //enemy.
    
    pDoc->enemyArray.push_back(enemy);
    //this->Invalidate();
    

    CView::OnLButtonDown(nFlags, point);
}
