#pragma once
#include "gameobject.h"
#include "Ball.h"
#include "Resource.h"

class CEnemy :
    public CGameObject
{
public:
    CEnemy(CPoint pos);
    CEnemy(CPoint pos,int motion);
    ~CEnemy(void);    
    
    BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		CRect rect = CRect(m_ptPos,CPoint(m_ptPos.x+ENEMY_HEIGHT,m_ptPos.y+ENEMY_HEIGHT));
        rect.top -= 2; //修正矩形 否则会有尾巴
        return rect;
	}

	int GetVerMontion() const;
    int GetHorMontion() const;
    void SetVerMotion(int motion);
    void SetHorMotion(int motion);
	//是否可以开火发射子弹
	BOOL Fired();
    void Invalidate();
    void Move();
    void Setm_V(int V);
    int Getm_V();
    static const int ENEMY_HEIGHT = 35;
    CBall ball[ENEMY_BALLS];
    //速度
	static int m_V;
    static void LevelUp(int level);
protected:
    void SetBallPos();
    void SetBallV();
    void SetBallMotion();

private:
	
	static CImageList m_Images;
	int    m_nVerMotion;//方向 1->向下 0->停止 -1->向上
    int    m_nHorMotion; //方向 1->向下 0->停止 -1->向上
	//图像索引
	int m_nImgIndex;
	
	int m_nWait;//发射延时
    //左右移动的宽度
    double hor_gap;
    double ver_gap;


    //测试用
public:
	static const int PLANE_WIDTH=32;
	static const int PLANE_HEIGHT=24;
public:
    
};
