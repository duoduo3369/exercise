#include "StdAfx.h"
#include "public.h"

int Move_Width = 32;
int Move_Height = 24;

CMyPlane::CMyPlane(void)
{
}

CMyPlane::~CMyPlane(void)
{
}



BOOL CMyPlane::Draw(CDC* pDC,BOOL bPause)
{
    //CPlaneDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return FALSE;

	// TODO: 在此处为本机数据添加绘制代码
    /*
    
    for(vector<CPoint>::iterator it = pDoc->pointArray.begin(); it != pDoc->pointArray.end(); ++it)
    {
        pDC->Rectangle(it->x,it->y,it->x+Move_Width,it->y+Move_Height);
    }
    if(!pDoc->pointArray.empty())
    {
        CBrush brush(RGB(0,0,0));
        RECT lastRect = GetLastRect(pDoc);
        pDC->FillRect(&lastRect,&brush);
        
    }
    */
    return TRUE;
}

/*
RECT GetLastRect(CPlaneDoc* pDoc)
{
        RECT lastRect;
        int lastRectIndex = pDoc->pointArray.size()-1;        
        CPoint lastRectOrign(pDoc->pointArray[lastRectIndex]);
        lastRect.left = lastRectOrign.x;
        lastRect.right = lastRect.left + Move_Width;
        lastRect.top = lastRectOrign.y;
        lastRect.bottom = lastRect.top + Move_Height;
        return lastRect;
}
*/