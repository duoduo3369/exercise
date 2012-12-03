#pragma once
#include "gameobject.h"

class CBall :
    public CGameObject
{
public:
    CBall(void);
    CBall(int x,int y,int nMontion);
    /*
    CBall(const CBall &ball);
    CBall& operator= (CBall &ball);
    */
    CBall(CPoint pos,int V,int nMontion);
	~CBall(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+BALL_HEIGHT,m_ptPos.y+BALL_HEIGHT));
	}
    int GetV();
    int GetMotion();
    void Invalidate();
    void Move();
    void SetV(int V);
    void SetPos(int x,int y);
    void SetMotion(int motion);
private:
	static const int BALL_HEIGHT=8;
	static CImageList m_Images;
	int    m_nMotion;
    int    m_V; //·ÉÐÐËÙ¶È

};
