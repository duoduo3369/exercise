#include "StdAfx.h"
#include "ToolUpBombSize.h"

CToolUpBombSize::CToolUpBombSize(void)
{
    isVisible = TRUE;
}

CToolUpBombSize::~CToolUpBombSize(void)
{
}
CToolUpBombSize::CToolUpBombSize(CPoint point)
{
    isVisible = TRUE;
    isActive = FALSE;
    m_ptPos = point;
}
unsigned int CToolUpBombSize::m_V = 5;
void CToolUpBombSize::SetActive(BOOL flag)
{
    isActive = flag;
}
void CToolUpBombSize::LevelUp()
{
    if(m_V > 3)
    {
        m_V--; 
    }
}
CRect CToolUpBombSize::GetRect()
{
		CRect rect = CRect(m_ptPos,CPoint(m_ptPos.x+WIDTH,m_ptPos.y+WIDTH));
        return rect;
}
void CToolUpBombSize::Do(CMyPlane &my)
{
    my.isBombUped = TRUE;
}
void CToolUpBombSize::Move()
{
    m_ptPos.y += m_V;
}
BOOL CToolUpBombSize::Draw(CDC* pDC,BOOL bPause)
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
        bmpMem.LoadBitmapW(IDB_WINE);
    
	    pbmpold = memDC.SelectObject(&bmpMem);
        pDC->BitBlt(SP_POS_X,SP_POS_Y,93,130,&memDC,0,0,SRCCOPY);
        
    }
    else
    {
        if(isVisible)
        {
            bmpMem.LoadBitmapW(IDB_BOMB_LEVEL_UP);    
	        pbmpold = memDC.SelectObject(&bmpMem);
	        pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,WIDTH,WIDTH,&memDC,0,0,WIDTH,WIDTH,RGB(0,0,0));   
        }
    }
    memDC.SelectObject(pbmpold);


    return TRUE;
}