#include "StdAfx.h"
#include "Enemy.h"
#include "Resource.h" 

//#include "GameObject.h"
CEnemy::CEnemy(CPoint pos):
    hor_gap(3.2),ver_gap(2.4),m_nVerMotion(DOWN_MOVE)//,m_V(2),
        
{
    m_nHorMotion = STATIC_MOVE;
    m_ptPos = pos;
    SetBallPos();
    SetBallV();
    SetBallMotion();
}

CEnemy::CEnemy(CPoint pos,int motion):
    hor_gap(3.2),ver_gap(2.4)//,m_V(2)
{
    m_nVerMotion = motion;
    m_nHorMotion = STATIC_MOVE;
    m_ptPos = pos;
    SetBallPos();
    SetBallV();
    SetBallMotion();
}
int CEnemy::m_V = 1;
void CEnemy::LevelUp(int level)
{
    switch(level)
    {
    case 2:
        {
            m_V++;
            break;
        }
    case 4:
        {
            m_V++;
            break;
        }
    case 7:
        {
            m_V++;
            break;
        }
    case 10:    
    case 12:
        {
            m_V++;
            break;
        }
    default:
        {
            return ;
        }
    }
}
CEnemy::~CEnemy(void)
{
    
}

void CEnemy::SetBallPos()
{

    ball[BALL_FRONT].SetPos(m_ptPos.x + ENEMY_HEIGHT / 2 - 5,m_ptPos.y + ENEMY_HEIGHT / 2);
    ball[BALL_BACK].SetPos(m_ptPos.x + ENEMY_HEIGHT / 2 + 5 ,m_ptPos.y + ENEMY_HEIGHT / 2);
}
void CEnemy::SetBallV()
{
    for(int i = 0; i < ENEMY_BALLS; i++)
    {
        ball[i].SetV(m_V * 2);
    }
        
}
void CEnemy::SetBallMotion()
{
    for(int i = 0; i < ENEMY_BALLS; i++)
    {
        ball[i].SetMotion(m_nVerMotion);
    }
}
void CEnemy::Invalidate()
{
    m_ptPos.x = -10000;
    m_ptPos.y = -10000;
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
	CBitmap *pbmpold = memDC.SelectObject(&bmpMem);
	pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,ENEMY_HEIGHT,ENEMY_HEIGHT,&memDC,0,0,ENEMY_HEIGHT,ENEMY_HEIGHT,RGB(0,0,0));
    memDC.SelectObject(pbmpold);

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

int CEnemy::GetVerMontion() const
{
	return m_nVerMotion;
}
int CEnemy::GetHorMontion() const
{
	return m_nHorMotion;
}
void CEnemy::SetVerMotion(int motion)
{
    m_nVerMotion = motion;
}
void CEnemy::SetHorMotion(int motion)
{
    m_nHorMotion = motion;
}
void CEnemy::Move()
{
    switch(m_nVerMotion)
    {
        case DOWN_MOVE: //向下
            m_ptPos.y += m_V;
            break;
        case STATIC_MOVE: //停止
            break;
        case UP_MOVE: //向上
            break;
    }
    switch(m_nHorMotion)
    {
        case LEFT_MOVE: //向左
            m_ptPos.x -= m_V ;
            break;
        case STATIC_MOVE: //停止
            break;
        case RIGHT_MOVE: //向右
            m_ptPos.x += m_V;
            break;
    }
    SetBallPos();
}