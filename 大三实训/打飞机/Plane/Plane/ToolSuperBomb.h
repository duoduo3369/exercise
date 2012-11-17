#pragma once
#include "tool.h"
#include "MyPlane.h"

class CToolSuperBomb :
    public CTool
{
public:
    CToolSuperBomb(void);
    ~CToolSuperBomb(void);
    CToolSuperBomb(CPoint point);
    BOOL Draw(CDC* pDC,BOOL bPause);
    void Do(CMyPlane &my);
    void Move();
    static void LevelUp();
    CRect GetRect();
    void SetActive(BOOL flag);
    //BOOL IsActive();
private:
    static const int WIDTH = 20;
    static unsigned int m_V;
};
