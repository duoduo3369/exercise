#pragma once
#include "tool.h"
#include "MyPlane.h"
class CToolLife :
    public CTool
{
public:
    CToolLife(void);
    ~CToolLife(void);
    CToolLife(CPoint point);
    BOOL Draw(CDC* pDC,BOOL bPause);
    void Do(CMyPlane &my);
    void Move();
    static void LevelUp();
    void SetActive(BOOL flag);
    CRect GetRect();
private:
    static const int WIDTH = 10;
    static unsigned int m_V;
};
