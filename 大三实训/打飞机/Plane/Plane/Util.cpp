#include "StdAfx.h"
#include "Util.h"
#include <ctime>
#include <cstdlib>

Util::Util(void)
{
    
}

Util::~Util(void)
{
}
int Util::GetRand(double min, double max)
{
    int MAX;
     MAX = RAND_MAX; //rand()函数随机数的最大值
     return (int)(rand()*(max-min)/MAX+min);
}
