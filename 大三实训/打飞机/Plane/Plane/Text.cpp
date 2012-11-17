#include "StdAfx.h"
#include "Text.h"

CText::CText(void)
{
}
CText::CText(int x,int y,CString string)
{
    m_ptPos.x = x;
    m_ptPos.y = y;
    outString = string;
}
CText::~CText(void)
{
}
void CText::SetPos(int x,int y)
{
    m_ptPos.x = x;
    m_ptPos.y = y;
}
void CText::SetString(CString string)
{
    outString = string;
}
BOOL CText::Draw(CDC* pDC,BOOL bPause)
{
    if(!pDC)
    {
        return FALSE;
    }    
    
    CDC memDC;
	memDC.CreateCompatibleDC(pDC);
    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(RGB(255,255,255));
    pDC->TextOutW(m_ptPos.x,m_ptPos.y,outString);
 
    return TRUE;
}