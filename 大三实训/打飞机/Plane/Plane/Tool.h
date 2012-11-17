#pragma once
#include "gameobject.h"
#include "MyPlane.h"
class CTool :
    public CGameObject
{
public:
    CTool(void);
    virtual ~CTool(void);
    virtual void Do(CMyPlane &my)=0;
    virtual void Move()=0;
    virtual void SetActive(BOOL flag)=0;
    BOOL isVisible;
protected:
    int    m_V; //·ÉÐÐËÙ¶È
    BOOL isActive;
    
};
