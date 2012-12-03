#pragma once
#include "gameobject.h"
#include "Explosion.h"
class CBomb :
    public CGameObject
{
public:
    CBomb();
    CBomb(const CBomb &bomb);
    CBomb(int x,int y);
	~CBomb(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
        CRect rect;
        rect.top = m_ptPos.y;
        rect.bottom = rect.top + BOMB_HEIGHT;
        rect.left = m_ptPos.x;
        rect.right = rect.left + BOMB_WIDTH;
		return rect;
	}
    void Invalidate();
    void Move();
    void SetVerMotion(int motion);
    void SetHorMotion(int motion);
    void SetV(int V);
    void SetPos(int x,int y);
private:
	static const int BOMB_HEIGHT = 20;
    static const int BOMB_WIDTH = 10;
	static CImageList m_Images;
    int    m_nVerMotion;
    int    m_nHorMotion;
    int    m_V; //·ÉÐÐËÙ¶È
    


};
