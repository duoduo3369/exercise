#include "StdAfx.h"
#include "ToolSpeedDown.h"

CToolSpeedDown::CToolSpeedDown(void)
{
    isVisible = TRUE;
}

CToolSpeedDown::~CToolSpeedDown(void)
{
}
CToolSpeedDown::CToolSpeedDown(CPoint point)
{
    isVisible = TRUE;
    isActive = FALSE;
    m_ptPos = point;
}
unsigned int CToolSpeedDown::m_V = 5;
void CToolSpeedDown::SetActive(BOOL flag)
{
    isActive = flag;
}
void CToolSpeedDown::LevelUp()
{
    if(m_V > 3)
    {
        m_V--; 
    }
}
CRect CToolSpeedDown::GetRect()
{
		CRect rect = CRect(m_ptPos,CPoint(m_ptPos.x+WIDTH,m_ptPos.y+WIDTH));
        return rect;
}
void CToolSpeedDown::Do(CMyPlane &my)
{
    my.DecreaseV();
}
void CToolSpeedDown::Move()
{
    m_ptPos.y += m_V;
}
BOOL CToolSpeedDown::Draw(CDC* pDC,BOOL bPause)
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
        bmpMem.LoadBitmapW(IDB_SPEED_SHORTAGE);
    
	    pbmpold = memDC.SelectObject(&bmpMem);
        pDC->BitBlt(SP_POS_X,SP_POS_Y,93,130,&memDC,0,0,SRCCOPY);
        
    }
    else
    {
        if(isVisible)
        {
            bmpMem.LoadBitmapW(IDB_SPEED_DOWN);    
	        pbmpold = memDC.SelectObject(&bmpMem);
        	pDC->TransparentBlt(m_ptPos.x,m_ptPos.y,WIDTH,WIDTH,&memDC,0,0,WIDTH,WIDTH,RGB(0,0,0));   
        }
    }
    memDC.SelectObject(pbmpold);


    return TRUE;
}