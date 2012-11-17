#include "StdAfx.h"
#include "ToolSuperBomb.h"

CToolSuperBomb::CToolSuperBomb(void)
{
    isVisible = TRUE;
}

CToolSuperBomb::~CToolSuperBomb(void)
{
}
CToolSuperBomb::CToolSuperBomb(CPoint point)
{
    isVisible = TRUE;
    isActive = FALSE;
    m_ptPos = point;
}
unsigned int CToolSuperBomb::m_V = 5;
void CToolSuperBomb::SetActive(BOOL flag)
{
    isActive = flag;
}
void CToolSuperBomb::LevelUp()
{
    if(m_V > 3)
    {
        m_V--; 
    }
}
CRect CToolSuperBomb::GetRect()
{
		CRect rect = CRect(m_ptPos,CPoint(m_ptPos.x+WIDTH,m_ptPos.y+WIDTH));
        return rect;
}
void CToolSuperBomb::Do(CMyPlane &my)
{
    my.SetSuperBomb(TRUE);
}
void CToolSuperBomb::Move()
{
    m_ptPos.y += m_V;
}
BOOL CToolSuperBomb::Draw(CDC* pDC,BOOL bPause)
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
        bmpMem.LoadBitmapW(IDB_ARCHERY_ATTCK);
    
	    pbmpold = memDC.SelectObject(&bmpMem);
        pDC->BitBlt(SP_POS_X,SP_POS_Y,93,130,&memDC,0,0,SRCCOPY);
        
    }
    else
    {
        if(isVisible)
        {
            bmpMem.LoadBitmapW(IDB_SUPERBOMB);    
	        pbmpold = memDC.SelectObject(&bmpMem);
	        pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,WIDTH,WIDTH,&memDC,0,0,WIDTH,WIDTH,RGB(0,0,0));   
        }
    }
    memDC.SelectObject(pbmpold);


    return TRUE;
}