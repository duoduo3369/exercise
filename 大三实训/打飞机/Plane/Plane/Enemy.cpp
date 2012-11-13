#include "StdAfx.h"
#include "Enemy.h"
//#include "GameObject.h"
CEnemy::CEnemy(CPoint pos):
    move_leftright_gap(3.2),move_updown_gap(2.4)
{
    m_ptPos = pos;
}
CEnemy::CEnemy(const CEnemy& enemy)
{
    m_Images = enemy.m_Images;
    m_nImgIndex = enemy.m_nImgIndex;
    m_nWait = enemy.m_nWait;
    m_ptPos = enemy.m_ptPos;
    m_V = enemy.m_V;
    move_leftright_gap = enemy.move_leftright_gap;
    move_updown_gap = enemy.move_updown_gap;
    m_nMotion = enemy.m_nMotion;
}

CEnemy& CEnemy::operator = (const CEnemy &enemy)
{
    m_Images = enemy.m_Images;
    m_nImgIndex = enemy.m_nImgIndex;
    m_nWait = enemy.m_nWait;
    m_ptPos = enemy.m_ptPos;
    m_V = enemy.m_V;
    move_leftright_gap = enemy.move_leftright_gap;
    move_updown_gap = enemy.move_updown_gap;
    m_nMotion = enemy.m_nMotion;
    return *this;
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

    pDC->Rectangle(m_ptPos.x,m_ptPos.y,m_ptPos.x+PLANE_WIDTH,m_ptPos.y+PLANE_HEIGHT);
    return TRUE;
}