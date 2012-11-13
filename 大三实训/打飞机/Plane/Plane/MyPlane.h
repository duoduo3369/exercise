#pragma once
#include "gameobject.h"

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
    void HorMove();
    void VerMove();
	CRect GetRect()
	{
		CRect rect = CRect(m_ptPos,CPoint(m_ptPos.x+PLANE_WIDTH,m_ptPos.y+PLANE_HEIGHT));
        rect.left -= 3;
        rect.right += 3;
        rect.top -= 2;
        return rect;
	}

	//�Ƿ���Կ����䵼��
	BOOL Fired();

public:
	static const int PLANE_WIDTH=50;
	static const int PLANE_HEIGHT=60;
private:
	
	static CImageList m_Images;
	int    m_nHorMotion;//�ɻ�ˮƽ���з���0->��ֹ��1->�� -1->��
	int    m_nVerMotion;//�ɻ���ֱ���з���0->��ֹ��1->�� -1->��
	int    m_nWait;//������ʱ
    int    m_V; //�����ٶ�

};
