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
     MAX = RAND_MAX; //rand()��������������ֵ
     return (int)(rand()*(max-min)/MAX+min);
}
