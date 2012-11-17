#include "StdAfx.h"
#include "ToolLife.h"
#include "Resource.h"
CToolLife::CToolLife(void)
{
    isVisible = TRUE;
    isActive = FALSE;
}

CToolLife::~CToolLife(void)
{
}
CToolLife::CToolLife(CPoint point)
{
    isVisible = TRUE;
    isActive = FALSE;
    m_ptPos = point;
}
unsigned int CToolLife::m_V = 7;
void CToolLife::LevelUp()
{
    if(m_V > 5)
    {
        m_V--; 
    }
}
CRect CToolLife::GetRect()
{
		CRect rect = CRect(m_ptPos,CPoint(m_ptPos.x+WIDTH,m_ptPos.y+WIDTH));
        return rect;
}
void CToolLife::Do(CMyPlane &my)
{
    my.IncreaseLife();
}
void CToolLife::Move()
{
    m_ptPos.y += m_V;
}
void CToolLife::SetActive(BOOL flag)
{
    isActive = flag;
}
BOOL CToolLife::Draw(CDC* pDC,BOOL bPause)
{
    if(!pDC)
    {
        return FALSE;
    }
    
    CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmpMem;
    CBitmap *pbmpold;
    if(isActive)
    {
        bmpMem.LoadBitmapW(IDB_PEACH);    
	    pbmpold = memDC.SelectObject(&bmpMem);
        pDC->BitBlt(SP_POS_X,SP_POS_Y,93,130,&memDC,0,0,SRCCOPY);
    }
    else
    {
        if(isVisible)
        {
            bmpMem.LoadBitmapW(IDB_LIFE);
	        pbmpold = memDC.SelectObject(&bmpMem);
	        pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,WIDTH,WIDTH,&memDC,0,0,WIDTH,WIDTH,RGB(255,255,255));
        }
    }
    
    memDC.SelectObject(pbmpold);


    return TRUE;
}