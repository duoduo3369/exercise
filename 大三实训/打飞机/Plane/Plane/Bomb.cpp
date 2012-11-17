#include "StdAfx.h"
#include "Bomb.h"
#include "public.h"

CBomb::CBomb():m_nVerMotion(STATIC_MOVE),m_nHorMotion(STATIC_MOVE)
{
}
CBomb::CBomb(int x,int y):m_nVerMotion(STATIC_MOVE),m_nHorMotion(STATIC_MOVE)
{
    m_ptPos.x = x;
    m_ptPos.y = y;    
}
CBomb::CBomb(const CBomb &bomb)
{
    m_nVerMotion = bomb.m_nVerMotion;
    m_V = bomb.m_V;
    m_ptPos.x = bomb.m_ptPos.x;
    m_ptPos.y = bomb.m_ptPos.y;  
    m_nHorMotion = bomb.m_nHorMotion;
}

CBomb::~CBomb(void)
{
}

void CBomb::SetVerMotion(int motion)
{
    m_nVerMotion = motion;
}
void CBomb::SetHorMotion(int motion)
{
    m_nHorMotion = motion;
}
void CBomb::SetV(int V)
{
    m_V = V;
}
void CBomb::SetPos(int x,int y)
{
    m_ptPos.x = x;
    m_ptPos.y = y;
}
void CBomb::Move()
{
    //if(m_nVerMotion && !m_nHorMotion)
    //{
    switch(m_nVerMotion)
    {
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
    //}
    //if(m_nHorMotion &&)
    switch(m_nHorMotion)
    {
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
void CBomb::Invalidate()
{
    m_ptPos.x = -10000;
    m_ptPos.y = -10000;
}
BOOL CBomb::Draw(CDC* pDC,BOOL bPause)
{
    if(!pDC)
    {
        return FALSE;
    }
    
    CDC memDC;
	memDC.CreateCompatibleDC(pDC);
    CBitmap *pbmpold;
	CBitmap bmpMem;
	
    switch(m_nHorMotion)
    {
    case LEFT_MOVE:
        {
            
            //if(m_nVerMotion)
            //{
                int BALL_HEIGHT = 8;
                bmpMem.LoadBitmapW(IDB_BALL_YELLOW);
	            pbmpold = memDC.SelectObject(&bmpMem);
	            pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,BALL_HEIGHT,BALL_HEIGHT,&memDC,0,0,BALL_HEIGHT,BALL_HEIGHT,RGB(0,0,0));
            /*
            }
            else
            {
                bmpMem.LoadBitmapW(IDB_BOMB_LEFT);
	            pbmpold = memDC.SelectObject(&bmpMem);
	            pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,BOMB_HEIGHT,BOMB_WIDTH,&memDC,0,0,BOMB_HEIGHT,BOMB_WIDTH,RGB(0,0,0));
            }
            
            */
        
            break;
        }
    case RIGHT_MOVE:
        {
            ///*
            //if(m_nVerMotion)
            //{
                int BALL_HEIGHT = 8;
                bmpMem.LoadBitmapW(IDB_BALL_YELLOW);
	            pbmpold = memDC.SelectObject(&bmpMem);	         
                pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,BALL_HEIGHT,BALL_HEIGHT,&memDC,0,0,BALL_HEIGHT,BALL_HEIGHT,RGB(0,0,0));
            /*
            }
            else
            {
                bmpMem.LoadBitmapW(IDB_BOMB_UP_RIGHT);
	            pbmpold = memDC.SelectObject(&bmpMem);
	            pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,BOMB_HEIGHT,BOMB_WIDTH,&memDC,0,0,BOMB_HEIGHT,BOMB_WIDTH,RGB(0,0,0));
            }
            */
            break;
        }
    default:
        {
            bmpMem.LoadBitmapW(IDB_BOMB);
	        pbmpold = memDC.SelectObject(&bmpMem);
	        pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,BOMB_WIDTH,BOMB_HEIGHT,&memDC,0,0,BOMB_WIDTH,BOMB_HEIGHT,RGB(0,0,0));
            break;
        }
    }

    
    
    
    memDC.SelectObject(pbmpold);


    return TRUE;
}