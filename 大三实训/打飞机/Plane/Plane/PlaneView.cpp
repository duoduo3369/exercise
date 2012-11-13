// PlaneView.cpp : CPlaneView 类的实现
//

#include "stdafx.h"
#include "public.h"
#include <cmath>
#include "PlaneView.h"

using namespace std;
//#include "GameObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneView

IMPLEMENT_DYNCREATE(CPlaneView, CView)

BEGIN_MESSAGE_MAP(CPlaneView, CView)
    //    ON_WM_LBUTTONDOWN()
    //    ON_WM_RBUTTONDOWN()
    //    ON_WM_KEYDOWN()
    //    ON_WM_TIMER()
    //    ON_WM_DESTROY()
    //ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONDOWN()
    ON_WM_TIMER()
    ON_WM_DESTROY()
    //ON_WM_ERASEBKGND()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CPlaneView 构造/析构

CPlaneView::CPlaneView()
    : pdc(NULL)
    , m_pMemDC(NULL)
    , m_pMemBitmap(NULL)
    , m_pOldBitmap(NULL)
{

}

CPlaneView::~CPlaneView()
{
    CPlaneDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    for(deque<CEnemy*>::iterator it = pDoc->enemyArray.begin(); it != pDoc->enemyArray.end(); ++it)
    {
        delete *it;
    }
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



void CPlaneView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CPlaneDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
    {
        return;
    }

    CEnemy *enemy =new CEnemy(point);

    pDoc->enemyArray.push_back(enemy);
    CRect enemyRect =  enemy->GetRect();

    this->InvalidateRect(enemyRect);

    CView::OnLButtonDown(nFlags, point);
}

void CPlaneView::OnTimer(UINT_PTR nIDEvent)
{
    CPlaneDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    if (!pDoc)
    {
        return;
    }

    switch(nIDEvent)
    {
    case TIMER_10://飞机移动
    {
        CRect rect;
        GetWindowRect(&rect);

        //我方飞机
        CPoint point = pDoc->myPlane->GetPoint();
        if(GetKeyState(VK_UP)<0)
        {

            if(point.y - pDoc->myPlane->GetV() - pDoc->myPlane->PLANE_HEIGHT*2 > 0)
            {
                pDoc->myPlane->SetVerMotion(UP_MOVE);
                pDoc->myPlane->VerMove();
            }
            else
            {
                pDoc->myPlane->SetVerMotion(STATIC_MOVE);
            }
        }
        if(GetKeyState(VK_DOWN)<0)
        {
            if(point.y + pDoc->myPlane->GetV() + pDoc->myPlane->PLANE_HEIGHT * 2.5 < rect.bottom)
            {
                pDoc->myPlane->SetVerMotion(DOWN_MOVE);
                pDoc->myPlane->VerMove();
            }
            else
            {
                pDoc->myPlane->SetVerMotion(STATIC_MOVE);
            }
        }
        if(GetKeyState(VK_LEFT)<0)
        {
            if(point.x - pDoc->myPlane->GetV() + pDoc->myPlane->PLANE_WIDTH /2 > 0)
            {
                pDoc->myPlane->SetHorMotion(LEFT_MOVE);
                pDoc->myPlane->HorMove();
            }
            else
            {
                pDoc->myPlane->SetHorMotion(STATIC_MOVE);
            }
        }
        if(GetKeyState(VK_RIGHT)<0)
        {
            if(point.x + pDoc->myPlane->GetV() + pDoc->myPlane->PLANE_WIDTH * 2 < rect.right)
            {
                pDoc->myPlane->SetHorMotion(RIGHT_MOVE);
                pDoc->myPlane->HorMove();
            }
            else
            {
                pDoc->myPlane->SetHorMotion(STATIC_MOVE);
            }
        }
        //this->InvalidateRect(pDoc->myPlane->GetRect());
        //敌方飞机
        for(deque<CEnemy*>::iterator it = pDoc->enemyArray.begin(); it != pDoc->enemyArray.end(); ++it)
        {

            (*it)->Move();
            CRect enemyRect = (*it)->GetRect();
            //this->InvalidateRect(enemyRect);

        }

        break;
    }

    case TIMER_40:
    {

        CPlaneDoc* pDoc = GetDocument();
        ASSERT_VALID(pDoc);
        if (!pDoc)
            return;
        CRect rect;
        GetWindowRect(&rect);

        CDC MemDC;
        //定义一个位图对象
        CBitmap MemBitmap;
        //建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）
        MemDC.CreateCompatibleDC(pdc);
        //这时还不能绘图，因为没有位图的设备描述表是不能绘图的
        //下面建立一个与屏幕设备描述表（或者内存设备描述表）兼容的位图
        MemBitmap.CreateCompatibleBitmap(pdc,1024,768);
        //将位图选入到内存设备描述表
        //只有选入了位图的设备描述表才有地方绘图，画到指定的位图上
        CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
        //先用背景色将位图清除干净，这里我用的是白色作为背景
        //你也可以用自己应该用的颜色
        MemDC.FillSolidRect(0,0,1024,768,RGB(255,255,255));
        //绘图


        for(deque<CEnemy*>::iterator it = pDoc->enemyArray.begin(); it != pDoc->enemyArray.end(); ++it)
        {
            (*it)->Draw(&MemDC,FALSE);
        }


        pDoc->myPlane->Draw(&MemDC,FALSE);
        pdc->BitBlt(0,0,1024,768,&MemDC,0,0,SRCCOPY);
        MemDC.SelectObject(pOldBit);
        MemBitmap.DeleteObject();
        MemDC.DeleteDC();
        break;
    }

    case TIMER_1000: //生成敌机
    {
        CRect rect;
        GetWindowRect(&rect);

        int max_x = RAND_MAX;
        int min_x = 0;
        int rand_x = Util::GetRand(0,rect.Width());
        CPoint point(rand_x,10);
        CEnemy *enemy =new CEnemy(point);

        pDoc->enemyArray.push_back(enemy);
        CRect enemyRect =  enemy->GetRect();

        break;
    }
    case TIMER_2000://销毁飞出屏幕的敌机
    {
        CRect rect;
        GetWindowRect(&rect);
        int gap = pDoc->enemyArray.front()->ENEMY_HEIGHT;
        unsigned int many = 0;
        for(deque<CEnemy*>::iterator it = pDoc->enemyArray.begin(); it != pDoc->enemyArray.end(); ++it)
        {
            CRect enemyRect = (*it)->GetRect();
            if(enemyRect.top > rect.bottom + gap || enemyRect.bottom < rect.top - gap || enemyRect.right < rect.left - gap || enemyRect.left > rect.right + gap)
            {
                many++;
            }
            else
            {
                break;
            }
        }

        while(many--)
        {
            CEnemy* enemy = pDoc->enemyArray.front();
            pDoc->enemyArray.pop_front();
            CRect enemyRect = enemy->GetRect();
            this->InvalidateRect(enemyRect);
            delete enemy;
        }

    }

    default:
    {
        break;
    }
    }

    CView::OnTimer(nIDEvent);
}

void CPlaneView::OnDestroy()
{
    CView::OnDestroy();
    KillTimer(TIMER_10);
    KillTimer(TIMER_40);
    KillTimer(TIMER_500);
    KillTimer(TIMER_1000);
    KillTimer(TIMER_2000);
}

void CPlaneView::OnInitialUpdate()
{
    CView::OnInitialUpdate();
    pdc = new CClientDC(this);
    SetTimer(TIMER_10,11,0);
    SetTimer(TIMER_40,10,0);
    SetTimer(TIMER_500,501,0);
    SetTimer(TIMER_1000,1001,0);
    SetTimer(TIMER_2000,2001,0);
    //初始化一架敌机
    CPlaneDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;
    CRect rect;
    GetWindowRect(&rect);

    int rand_x = Util::GetRand(0,rect.Height());
    CPoint pointEnemy(rand_x,10);
    CEnemy *enemy =new CEnemy(pointEnemy);
    pDoc->enemyArray.push_back(enemy);
    CPoint pointMe(rect.Width()/2,rect.Height()-CMyPlane::PLANE_HEIGHT*2);
    pDoc->myPlane = new CMyPlane(pointMe);
}

BOOL CPlaneView::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}
