// PlaneDoc.h : CPlaneDoc 类的接口
//


#pragma once
//#include<vector> 
#include <deque>
#include "MyPlane.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"
#include "PlaneGame.h"
#include "Text.h"
#include "Tool.h"
using namespace std;


class CPlaneDoc : public CDocument
{
protected: // 仅从序列化创建
	CPlaneDoc();
	DECLARE_DYNCREATE(CPlaneDoc)

// 属性
public:
    
    deque<CEnemy*> enemyArray;
    deque<CBomb*> bombArray;
    deque<CBall*> ballArray;
    deque<CExplosion*> explosionArray;
    CText outText[OUT_STRINGS];
    deque<CTool*> toolArray;
    CMyPlane *myPlane;
    CPlaneGame game;
    unsigned int backCount;
// 操作
public:
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CPlaneDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};


