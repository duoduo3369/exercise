#pragma once
#include "tool.h"

class CToolSpeedUp :
    public CTool
{
public:
    CToolSpeedUp(void);
    ~CToolSpeedUp(void);
    CToolSpeedUp(CPoint point);
    BOOL Draw(CDC* pDC,BOOL bPause);
    void Do(CMyPlane &my);
    void Move();
    static void LevelUp();
    CRect GetRect();
    void SetActive(BOOL flag);
private:
    static const int WIDTH = 20;
    static unsigned int m_V;
};
