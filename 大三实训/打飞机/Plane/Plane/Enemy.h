#pragma once
#include "gameobject.h"

class CEnemy :
    public CGameObject
{
public:
    CEnemy(CPoint pos);
    CEnemy(const CEnemy& enemy);
    ~CEnemy(void);
    CEnemy& operator = (const CEnemy &enemy);
    BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+ENEMY_HEIGHT,m_ptPos.y+ENEMY_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	//是否可以开火发射子弹
	BOOL Fired();
private:
	static const int ENEMY_HEIGHT = 35;
	static CImageList m_Images;
	int    m_nMotion;//方向 1->向下 0->停止 -1->向上
	//图像索引
	int m_nImgIndex;
	//速度
	int m_V;
	int m_nWait;//发射延时
    //左右移动的宽度
    double move_leftright_gap;
    double move_updown_gap;


    //测试用
public:
	static const int PLANE_WIDTH=32;
	static const int PLANE_HEIGHT=24;
public:
    
};
