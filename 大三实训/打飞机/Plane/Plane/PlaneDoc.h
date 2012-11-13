// PlaneDoc.h : CPlaneDoc ��Ľӿ�
//


#pragma once
#include<vector> 
#include "MyPlane.h"
#include "Enemy.h"

using namespace std;


class CPlaneDoc : public CDocument
{
protected: // �������л�����
	CPlaneDoc();
	DECLARE_DYNCREATE(CPlaneDoc)

// ����
public:
    vector<CEnemy> enemyArray;
    CMyPlane myPlane;
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


