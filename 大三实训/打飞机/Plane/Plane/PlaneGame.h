#pragma once
#include "Bomb.h"
#include "MyPlane.h"
#include "Enemy.h"
class CPlaneGame
{
public:
    CPlaneGame(void);
    ~CPlaneGame(void);
    void AI(CEnemy &enemy,CMyPlane &my);
    BOOL IsGameObjectValidate(CRect &objectRect,CRect &clientRect);
    int GetGrade() const;
    void UpGrade(int grade);
    void LevelUp();
    BOOL IsLevelUp();
    unsigned int level;
    BOOL DrawBackGround(CDC* pDC,BOOL bPause);
    unsigned int GetSpecialSize();
    int GetEnemyLimits() const;
    CRect GclientRect;
private:
    int GetBackBmpID();
    unsigned int grade;
    BOOL specialToolActive;
    unsigned int backPos;//ʹ�����ƶ�������
    unsigned int backPos_i;//���경����
    int countAI; //��ɻ��ƶ��й�
    
    
};
