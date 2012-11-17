#include "StdAfx.h"
#include "PlaneGame.h"
#include "Resource.h"
#include "Enemy.h"
#include "ToolLife.h"
CPlaneGame::CPlaneGame(void):grade(0),level(1),backPos(0),backPos_i(0),countAI(0)
{
}

CPlaneGame::~CPlaneGame(void)
{
}
void CPlaneGame::UpGrade(int grade)
{
    this->grade += grade;
}
int CPlaneGame::GetGrade() const
{
    return grade;
}
int CPlaneGame::GetEnemyLimits() const
{
    
    unsigned int many = 15 * level;
    many = many > 45 ? 45 : many;
    return many;
}
BOOL CPlaneGame::IsLevelUp()
{
    switch(level)
    {
    case 1:
        {
            return (2048 < grade);
        }
    case 2:
        {
            return (20240 < grade);
        }
    case 3:
        {
            return (45480 < grade);
        }
    case 4:
        {
            return (75480 < grade);
        }
    case 5:
        {
            return (90592 < grade);
        }
    }
    return (level * level * 3072 < grade);
}
unsigned int CPlaneGame::GetSpecialSize()
{
    return level;
}
void CPlaneGame::LevelUp()
{
    level++;
    if(CEnemy::m_V < 7)
    {
        CEnemy::LevelUp(level);
    }            
    CToolLife::LevelUp();
}

BOOL CPlaneGame::IsGameObjectValidate(CRect &objectRect,CRect &clientRect)
{
    return (objectRect.top > clientRect.bottom || objectRect.bottom <  clientRect.top || objectRect.right < clientRect.left || objectRect.left > clientRect.right);
}

void CPlaneGame::AI(CEnemy &enemy,CMyPlane &my)
{
    CRect enemyRect,myRect;
    enemyRect = enemy.GetRect();
    myRect = my.GetRect();
    enemy.SetVerMotion(DOWN_MOVE);
    countAI = (countAI + 1) % 3;
    if(myRect.right > enemyRect.left - my.PLANE_WIDTH && myRect.left < enemyRect.left)
    {
        enemy.SetHorMotion(LEFT_MOVE);
        if(myRect.top < enemyRect.bottom + my.PLANE_HEIGHT && myRect.bottom > enemyRect.top)
        {
            enemy.SetVerMotion(STATIC_MOVE);
        }
            
    }
    else if(myRect.left < enemyRect.right + my.PLANE_WIDTH && myRect.right > enemyRect.right)
    {
        enemy.SetHorMotion(RIGHT_MOVE);        
        if(myRect.top < enemyRect.bottom + my.PLANE_HEIGHT && myRect.bottom > enemyRect.top)
        {
            enemy.SetVerMotion(STATIC_MOVE);
        }
    }

    //敌方飞机没有碰到我方飞机时左右移动
    
    else if(enemyRect.top > GclientRect.Height()/2)
    {
        if(enemyRect.left > GclientRect.Width() / 2 && enemy.GetHorMontion()!=RIGHT_MOVE)
        {
            enemy.SetHorMotion(LEFT_MOVE);
        }
        else if(enemyRect.right < GclientRect.Width() / 2 && enemy.GetHorMontion()!=LEFT_MOVE)
        {
            enemy.SetHorMotion(RIGHT_MOVE); 
        }
    }
    /*
    else if(enemyRect.top > GclientRect.Height()/3*2)
    {
        if(countAI && enemyRect.left > GclientRect.Width() / 2)
        {
            enemy.SetHorMotion(LEFT_MOVE);
        }
        else if(enemyRect.left < GclientRect.Width() / 2)
        {
            enemy.SetHorMotion(RIGHT_MOVE); 
        }
        
    }
    */
    else
    {
        enemy.SetHorMotion(STATIC_MOVE); 
        //enemy.SetVerMotion(DOWN_MOVE);
    }

    
}
int CPlaneGame::GetBackBmpID()
{
    int i = level % 3;
    switch(i)
    {
    case 0:
        {
            return IDB_BACK_WEI;
        }
    case 1:
        {
            return IDB_BACK_SHU;
        }
    case 2:
        {
            return IDB_BACK_WU;
        }
    }
    return 0;
}
BOOL CPlaneGame::DrawBackGround(CDC* pDC,BOOL bPause)
{
    if(!pDC)
    {
        return FALSE;
    }
    int width = 383;
    int height = 648;
    backPos_i--;
    backPos_i = (backPos_i + height) % height;
    if(backPos_i % 5 == 0)
    {
        backPos--;
        backPos = (backPos + height) % height;
    }
    CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmpMem;
	bmpMem.LoadBitmapW(GetBackBmpID());
	CBitmap *pbmpold = memDC.SelectObject(&bmpMem);
    //pDC->BitBlt(0,0,width,height,&memDC,0,0,SRCCOPY);
    pDC->BitBlt(0,0,width,height,&memDC,0,backPos,SRCCOPY);
    pDC->BitBlt(0,height-backPos,width,height,&memDC,0,0,SRCCOPY);

	//pDC->TransparentBlt(0,0,496,436,&memDC,0,0,496,436,RGB(0,0,0));
    memDC.SelectObject(pbmpold);

    return TRUE;
}
