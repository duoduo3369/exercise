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
        rect.top -= 2; //�������� �������β��
        return rect;
	}

	int GetUpDownMontion() const
	{
		return m_n_updown_Motion;
	}
	//�Ƿ���Կ������ӵ�
	BOOL Fired();
    void Move();
    void Setm_V(int V);
    int Getm_V();
    void LevelUp(int V);//�����ٶ�����
    static const int ENEMY_HEIGHT = 35;

private:
    
	
	static CImageList m_Images;
	int    m_n_updown_Motion;//���� 1->���� 0->ֹͣ -1->����
    int    m_n_leftright_Motion; //���� 1->���� 0->ֹͣ -1->����
	//ͼ������
	int m_nImgIndex;
	//�ٶ�
	int m_V;
	int m_nWait;//������ʱ
    //�����ƶ��Ŀ��
    double move_leftright_gap;
    double move_updown_gap;


    //������
public:
	static const int PLANE_WIDTH=32;
	static const int PLANE_HEIGHT=24;
public:
    
};
