// PlaneView.cpp : CPlaneView ���ʵ��
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

// CPlaneView ����/����

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
    // TODO: �ڴ˴�ͨ���޸�
    //  CREATESTRUCT cs ���޸Ĵ��������ʽ

    return CView::PreCreateWindow(cs);
}

// CPlaneView ����

void CPlaneView::OnDraw(CDC* pDC)
{

}


// CPlaneView ���

#ifdef _DEBUG
void CPlaneView::AssertValid() const
{
    CView::AssertValid();
}

void CPlaneView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CPlaneDoc* CPlaneView::GetDocument() const // �ǵ��԰汾��������
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
    case TIMER_10://�ɻ��ƶ�
    {
        CRect rect;
        GetWindowRect(&rect);

        //�ҷ��ɻ�
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
        //�з��ɻ�
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
        //����һ��λͼ����
        CBitmap MemBitmap;
        //��������Ļ�豸������ǰ�˻����������ݵ��ڴ��豸�����������󱸻�������
        MemDC.CreateCompatibleDC(pdc);
        //��ʱ�����ܻ�ͼ����Ϊû��λͼ���豸�������ǲ��ܻ�ͼ��
        //���潨��һ������Ļ�豸�����������ڴ��豸���������ݵ�λͼ
        MemBitmap.CreateCompatibleBitmap(pdc,1024,768);
        //��λͼѡ�뵽�ڴ��豸������
        //ֻ��ѡ����λͼ���豸��������еط���ͼ������ָ����λͼ��
        CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
        //���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����
        //��Ҳ�������Լ�Ӧ���õ���ɫ
        MemDC.FillSolidRect(0,0,1024,768,RGB(255,255,255));
        //��ͼ


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

    case TIMER_1000: //���ɵл�
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
    case TIMER_2000://���ٷɳ���Ļ�ĵл�
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
    //��ʼ��һ�ܵл�
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
