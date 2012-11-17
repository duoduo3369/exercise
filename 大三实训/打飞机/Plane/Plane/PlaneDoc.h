// PlaneDoc.h : CPlaneDoc ��Ľӿ�
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
protected: // �������л�����
	CPlaneDoc();
	DECLARE_DYNCREATE(CPlaneDoc)

// ����
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
// ����
public:
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CPlaneDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


