#pragma once
#include "GameObject.h"
class CExplosion :public CGameObject
{
public:
    CExplosion();
	CExplosion(int x,int y);
    ~CExplosion(void){}

	BOOL Draw(CDC* pDC,BOOL bPause);

	BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+EXPLOSION_WIDTH,m_ptPos.y+EXPLOSION_WIDTH));
	}
    void SetPos(int x,int y);
    void Invalidate();
    BOOL IsDrawDone();
private:
	//炸弹的图片列表
	CImageList m_Images;
	//图像索引的步进计数
	int   m_nProcess;
public:
	static const int  EXPLOSION_WIDTH = 66;

};
