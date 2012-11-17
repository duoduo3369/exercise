#pragma once
#include "gameobject.h"

class CText :
    public CGameObject
{
public:
    CText(void);
    CText(int x,int y,CString string);
	~CText(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

    void SetPos(int x,int y);
    void SetString(CString string);
	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x,m_ptPos.y));
	}
    CString outString;
};
