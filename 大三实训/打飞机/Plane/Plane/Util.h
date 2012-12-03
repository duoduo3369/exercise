#pragma once
#include "afx.h"

class Util :
    public CObject
{
public:
    Util(void);
    ~Util(void);
    static int GetRand(double min, double max);//产生随机数
    
};
