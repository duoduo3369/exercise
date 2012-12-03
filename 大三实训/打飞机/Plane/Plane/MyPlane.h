#pragma once
#include "gameobject.h"
#include "Bomb.h"
#include "Resource.h"
class CMyPlane :
    public CGameObject
{
public:
    CMyPlane(void);
    CMyPlane(CPoint pos);
    ~CMyPlane(void);
    BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	void SetHorMotion(int nMotion)
	{
		m_nHorMotion = nMotion;
	}
	int GetHorMotion() const
	{
		return m_nHorMotion;
	}
    int GetV() const
    {
        return m_V;
    }
    
	void SetVerMotion(int nMotion)
	{
		m_nVerMotion = nMotion;
	}
	int GetVerMotion() const
	{
		return m_nVerMotion;
	}
    void IncreaseV();
    void DecreaseV();
    
    void HorMove();
    void VerMove();
    int GetLife() const;
    void IncreaseLotsLife();
	CRect GetRect()
	{
		CRect rect = CRect(m_ptPos,CPoint(m_ptPos.x+PLANE_WIDTH,m_ptPos.y+PLANE_HEIGHT));
        rect.left -= 3;
        rect.right += 3;
        rect.top -= 2;
        return rect;
	}

	//是否可以开火发射导弹
	BOOL Fired();

public:
	static const int PLANE_WIDTH=50;
	static const int PLANE_HEIGHT=60;
    CBomb  bomb[MYPLANE_BOMBS];//炸弹默认5发 前面两发，左右下各一发
    void SetSuperBomb(BOOL flag);
    BOOL   isBombUped;
    BOOL IsSuperBombAvilible();
    BOOL IsAlive();
    void DecreaseLife();
    void IncreaseLife();
    void Invalidate();
    void ReInitPlane(const CRect &clientRect);
    BOOL IsSuperBombFired();
    void SetSuperBombFired(BOOL flag);

protected:
    void SetBombPos();
    void SetBombV();
    void SetBombMotion();
    void SetCenterPos(const CRect &clientRect);

private:
	
	static CImageList m_Images;
	int    m_nHorMotion;//飞机水平运行方向0->静止，1->右 -1->左
	int    m_nVerMotion;//飞机垂直运行方向0->静止，1->上 -1->下
	int    m_nWait;//发射延时
    int    m_V; //飞行速度
    BOOL   superBomb;
    BOOL   issuperbomb_fired;
    
    unsigned int    m_life;
};
