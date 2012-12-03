#include "StdAfx.h"
#include "Ball.h"
#include "Resource.h"
CBall::CBall(void)
{
}
CBall::CBall(int x,int y,int nMontion)
{
    m_ptPos.x = x;
    m_ptPos.y = y;
    m_nMotion = nMontion;
}
CBall::CBall(CPoint pos,int V,int nMontion)
{
    m_ptPos = pos;
    m_nMotion = nMontion;
    m_V = V;
    
}
int CBall::GetV()
{
    return m_V;
}
int CBall::GetMotion()
{
    return m_nMotion;
}

CBall::~CBall(void)
{
}

void CBall::SetV(int V)
{
    m_V = V;
}
void CBall::SetPos(int x,int y)
{
    m_ptPos.x = x;
    m_ptPos.y = y;
}
void CBall::SetMotion(int motion)
{
    m_nMotion = motion;
}
void CBall::Move()
{
    switch(m_nMotion)
    {
    case DOWN_MOVE:
        {
            m_ptPos.y += m_V;
            break;
        }
    case UP_MOVE:
        {
            m_ptPos.y -= m_V;
            break;
        }
    }
}
void CBall::Invalidate()
{
    m_ptPos.x = -10000;
    m_ptPos.y = -10000;
}
BOOL CBall::Draw(CDC* pDC,BOOL bPause)
{
    if(!pDC)
    {
        return FALSE;
    }
    CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmpMem;
	bmpMem.LoadBitmapW(IDB_BALL);
	CBitmap *pbmpold(memDC.SelectObject(&bmpMem));
    //memDC.TransparentBlt(m_ptPos.x,m_ptPos.y,BALL_HEIGHT,BALL_HEIGHT,&memDC,0,0,BALL_HEIGHT,BALL_HEIGHT,RGB(0,0,0));
	//pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,BALL_HEIGHT,BALL_HEIGHT,&memDC,0,0,BALL_HEIGHT,BALL_HEIGHT,RGB(255,255,255));
    pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,BALL_HEIGHT,BALL_HEIGHT,&memDC,0,0,BALL_HEIGHT,BALL_HEIGHT,RGB(0,0,0));


    return TRUE;
}
