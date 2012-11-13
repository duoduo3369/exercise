#include "StdAfx.h"
#include "Enemy.h"
#include "Resource.h" 
//#include "GameObject.h"
CEnemy::CEnemy(CPoint pos):
    move_leftright_gap(3.2),move_updown_gap(2.4),m_V(2),
        m_n_updown_Motion(1)
{
    m_ptPos = pos;
}

CEnemy::~CEnemy(void)
{
    
}
BOOL CEnemy::Draw(CDC* pDC,BOOL bPause)
{
    if(!pDC)
    {
        return FALSE;
    }

    CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmpMem;
    
	bmpMem.LoadBitmapW(IDB_ENEMY);
	CBitmap *pbmpold(memDC.SelectObject(&bmpMem));
    memDC.TransparentBlt(m_ptPos.x,m_ptPos.y,ENEMY_HEIGHT,ENEMY_HEIGHT,&memDC,0,0,ENEMY_HEIGHT,ENEMY_HEIGHT,RGB(0,0,0));
	pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,ENEMY_HEIGHT,ENEMY_HEIGHT,&memDC,0,0,ENEMY_HEIGHT,ENEMY_HEIGHT,RGB(0,0,0));


    return TRUE;
}

void CEnemy::Setm_V(int V)
{
    m_V = V;
}
int CEnemy::Getm_V()
{
    return m_V;
}

void CEnemy::LevelUp(int V)//升级速度增加V
{
    m_V += V;
}

void CEnemy::Move()
{
    //if(m_n_updown_Motion == 1)
    switch(m_n_updown_Motion)
    {
        case 1: //向下
            m_ptPos.y += m_V;
            break;
        case 0: //停止
            break;
        case -1: //向上
            break;
    }
}