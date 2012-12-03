#include "StdAfx.h"
#include "public.h"
#include "Resource.h"

CMyPlane::CMyPlane(void):m_V(3),superBomb(TRUE),m_life(5),issuperbomb_fired(FALSE),isBombUped(FALSE)
{

    SetBombV();
    SetBombPos();
    SetBombMotion();
    for(int i = 0; i < MYPLANE_BOMBS;i++)
    {
        bomb[i].SetV(int(m_V * 2));
    } 
}

CMyPlane::CMyPlane(CPoint pos):
    m_nHorMotion(STATIC_MOVE),m_nVerMotion(STATIC_MOVE),m_V(3),superBomb(TRUE),m_life(5),issuperbomb_fired(FALSE),isBombUped(FALSE)
{
    m_ptPos = pos;
    SetBombV();
    SetBombPos();
    SetBombMotion();
}

CMyPlane::~CMyPlane(void)
{

}
void CMyPlane::SetSuperBombFired(BOOL flag)
{
   issuperbomb_fired = flag;
}
BOOL CMyPlane::IsSuperBombFired()
{
    return issuperbomb_fired;
}
void CMyPlane::SetBombV()
{
    for(int i = 0; i < MYPLANE_BOMBS;i++)
    {
        bomb[i].SetV(int(m_V * 2));
    }    
}
void CMyPlane::SetSuperBomb(BOOL flag)
{
    superBomb = flag;
}
BOOL CMyPlane::IsSuperBombAvilible()
{
    return superBomb;
}
void CMyPlane::DecreaseLife()
{
    m_life--;
    m_life = m_life < 0 ? 0 : m_life;
}
void CMyPlane::IncreaseLife()
{
    m_life++;
}
void CMyPlane::Invalidate()
{
    m_ptPos.x = -10000;
    m_ptPos.y = -10000;
}
BOOL CMyPlane::IsAlive()
{
    return (m_life > 0);
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
    SetBombPos();
}
int CMyPlane::GetLife() const
{
    return m_life;
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
    SetBombPos();
}
void CMyPlane::SetCenterPos(const CRect &clientRect)
{
    m_ptPos.x = clientRect.Width() / 2;
    m_ptPos.y = clientRect.Height() / 2;
}
void CMyPlane::SetBombPos()
{
    int width = PLANE_WIDTH / 2;
    int height = PLANE_HEIGHT / 2;
    bomb[BOMB_UP_LEFT].SetPos(m_ptPos.x + width - 13,m_ptPos.y);
    bomb[BOMB_UP_RIGHT].SetPos(m_ptPos.x + width + 3,m_ptPos.y);
    bomb[BOMB_LEFT].SetPos(m_ptPos.x + width-15,m_ptPos.y+height-10);
    bomb[BOMB_RIGHT].SetPos(m_ptPos.x + width+5,m_ptPos.y+height-10);
    bomb[BOMB_MID_LEFT].SetPos(m_ptPos.x + width - 20,m_ptPos.y);
    bomb[BOMB_MID_RIGHT].SetPos(m_ptPos.x + width + 10,m_ptPos.y); 
    bomb[BOMB_BALL_LEFT].SetPos(m_ptPos.x + width - 20,m_ptPos.y);
    bomb[BOMB_BALL_RIGHT].SetPos(m_ptPos.x + width + 10,m_ptPos.y); 
        
    
}
void CMyPlane::SetBombMotion()
{
    bomb[BOMB_UP_LEFT].SetVerMotion(UP_MOVE);
    bomb[BOMB_UP_RIGHT].SetVerMotion(UP_MOVE);
    bomb[BOMB_MID_LEFT].SetVerMotion(UP_MOVE);
    bomb[BOMB_MID_RIGHT].SetVerMotion(UP_MOVE);
    bomb[BOMB_LEFT].SetHorMotion(LEFT_MOVE);
    bomb[BOMB_RIGHT].SetHorMotion(RIGHT_MOVE);
    bomb[BOMB_BALL_LEFT].SetHorMotion(LEFT_MOVE);
    bomb[BOMB_BALL_RIGHT].SetHorMotion(RIGHT_MOVE);
    bomb[BOMB_BALL_LEFT].SetVerMotion(UP_MOVE);
    bomb[BOMB_BALL_RIGHT].SetVerMotion(UP_MOVE);

}
void CMyPlane::ReInitPlane(const CRect &clientRect)
{
    SetCenterPos(clientRect);
    SetBombPos();
    SetBombV();
    m_life = 5;
}
BOOL CMyPlane::Fired()
{
    return IsAlive();
}
void CMyPlane::IncreaseLotsLife()
{
    m_life += 100;
}
void CMyPlane::IncreaseV()
{
    if(m_V < 5)
    {
        m_V++;
    }    
}
void CMyPlane::DecreaseV()
{
    if(m_V > 2)
    {
        m_V--;
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
	CBitmap *pbmpold = memDC.SelectObject(&bmpMem);
	pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,PLANE_WIDTH,PLANE_HEIGHT,&memDC,0,0,PLANE_WIDTH,PLANE_HEIGHT,RGB(0,0,0));
    
    memDC.SelectObject(pbmpold);


    return TRUE;
}

