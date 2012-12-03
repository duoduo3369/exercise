#include "StdAfx.h"
#include "Explosion.h"
#include "Resource.h"
CExplosion::CExplosion(int x,int y):m_nProcess(0)
{
    m_ptPos.x = x;
    m_ptPos.y = y;
    LoadImage();
}
CExplosion::CExplosion():m_nProcess(0)
{
    LoadImage();
}
void CExplosion::Invalidate()
{
    m_ptPos.x = -10000;
    m_ptPos.y = -10000;
}
BOOL CExplosion::IsDrawDone()
{
    if(m_nProcess==8)
	{
		return TRUE;
	}
    return FALSE;
}
BOOL CExplosion::Draw(CDC* pDC,BOOL bPause)
{
	if(m_nProcess==8)
	{
		m_nProcess=0;
		return FALSE;
	}
	m_Images.Draw(pDC,m_nProcess,m_ptPos,ILD_TRANSPARENT);
	m_nProcess++;
	return TRUE;
}
void CExplosion::SetPos(int x,int y)
{
    m_ptPos.x = x;
    m_ptPos.y = y;
}
BOOL CExplosion::LoadImage()
{
	CBitmap bmp;
	if(!bmp.LoadBitmapW(IDB_EXPLOSION))
		return FALSE;
	if(!m_Images.Create(66,66, ILC_COLOR24|ILC_MASK,8,0))
		return FALSE;
	m_Images.Add(&bmp,RGB(0,0,0));
	return TRUE;
}