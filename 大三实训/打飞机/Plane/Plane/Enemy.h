#pragma once
#include "gameobject.h"

class CEnemy :
    public CGameObject
{
public:
    CEnemy(CPoint pos);
    ~CEnemy(void);    
    
    BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		CRect rect = CRect(m_ptPos,CPoint(m_ptPos.x+ENEMY_HEIGHT,m_ptPos.y+ENEMY_HEIGHT));
        rect.top -= 2; //修正矩形 否则会有尾巴
        return rect;
	}

	int GetUpDownMontion() const
	{
		return m_n_updown_Motion;
	}
	//是否可以开火发射子弹
	BOOL Fired();
    void Move();
    void Setm_V(int V);
    int Getm_V();
    void LevelUp(int V);//升级速度增加
    static const int ENEMY_HEIGHT = 35;

private:
    
	
	static CImageList m_Images;
	int    m_n_updown_Motion;//方向 1->向下 0->停止 -1->向上
    int    m_n_leftright_Motion; //方向 1->向下 0->停止 -1->向上
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
