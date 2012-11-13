#include "StdAfx.h"
#include "public.h"


CMyPlane::CMyPlane(void)
{
}
CMyPlane::CMyPlane(CPoint pos):
    m_nHorMotion(STATIC_MOVE),m_nVerMotion(STATIC_MOVE),m_V(3)
{
    m_ptPos = pos;
}


CMyPlane::~CMyPlane(void)
{

}

void CMyPlane::HorMove()
{
    switch(m_nHorMotion)
    {
        case STATIC_MOVE:
            {
                break;
            }
        case LEFT_MOVE:
            {
                m_ptPos.x -= m_V;
                break;
            }
        case RIGHT_MOVE:
            {
                m_ptPos.x += m_V;
                break;            
            }
    }    

}
void CMyPlane::VerMove()
{
    switch(m_nVerMotion)
    {
        case STATIC_MOVE:
            {
                break;
            }
        case UP_MOVE:
            {
                m_ptPos.y -= m_V;
                break;
            }
        case DOWN_MOVE:
            {
                m_ptPos.y += m_V;
                break;            
            }
    }
}

BOOL CMyPlane::Draw(CDC* pDC,BOOL bPause)
{
    if(!pDC)
    {
        return FALSE;
    }
    CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmpMem;
	bmpMem.LoadBitmapW(IDB_MYPLANE);
	CBitmap *pbmpold(memDC.SelectObject(&bmpMem));
    memDC.TransparentBlt(m_ptPos.x,m_ptPos.y,PLANE_WIDTH,PLANE_HEIGHT,&memDC,0,0,PLANE_WIDTH,PLANE_HEIGHT,RGB(0,0,0));
	pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,PLANE_WIDTH,PLANE_HEIGHT,&memDC,0,0,PLANE_WIDTH,PLANE_HEIGHT,RGB(0,0,0));


    return TRUE;
}

