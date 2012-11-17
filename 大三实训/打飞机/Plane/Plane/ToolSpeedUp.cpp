#include "StdAfx.h"
#include "ToolSpeedUp.h"

CToolSpeedUp::CToolSpeedUp(void)
{
    isVisible = TRUE;
}

CToolSpeedUp::~CToolSpeedUp(void)
{
}
CToolSpeedUp::CToolSpeedUp(CPoint point)
{
    isVisible = TRUE;
    isActive = FALSE;
    m_ptPos = point;
}
unsigned int CToolSpeedUp::m_V = 5;
void CToolSpeedUp::SetActive(BOOL flag)
{
    isActive = flag;
}
void CToolSpeedUp::LevelUp()
{
    if(m_V > 3)
    {
        m_V--; 
    }
}
CRect CToolSpeedUp::GetRect()
{
		CRect rect = CRect(m_ptPos,CPoint(m_ptPos.x+WIDTH,m_ptPos.y+WIDTH));
        return rect;
}
void CToolSpeedUp::Do(CMyPlane &my)
{
    my.IncreaseV();
}
void CToolSpeedUp::Move()
{
    m_ptPos.y += m_V;
}
BOOL CToolSpeedUp::Draw(CDC* pDC,BOOL bPause)
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
        bmpMem.LoadBitmapW(IDB_SPEED_DAWAN);
    
	    pbmpold = memDC.SelectObject(&bmpMem);
        pDC->BitBlt(SP_POS_X,SP_POS_Y,93,130,&memDC,0,0,SRCCOPY);
        
    }
    else
    {
        if(isVisible)
        {
            bmpMem.LoadBitmapW(IDB_SPEED_UP);    
	        pbmpold = memDC.SelectObject(&bmpMem);
	        pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,WIDTH,WIDTH,&memDC,0,0,WIDTH,WIDTH,RGB(0,0,0));   
        }
    }
    memDC.SelectObject(pbmpold);


    return TRUE;
}