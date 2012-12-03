#pragma once
#include "tool.h"

class CToolSpeedDown :
    public CTool
{
public:
    CToolSpeedDown(void);
    ~CToolSpeedDown(void);
    CToolSpeedDown(CPoint point);
    BOOL Draw(CDC* pDC,BOOL bPause);
    void Do(CMyPlane &my);
    void Move();
    static void LevelUp();
    CRect GetRect();
    void SetActive(BOOL flag);
private:
    static const int WIDTH = 10;
    static unsigned int m_V;
};
