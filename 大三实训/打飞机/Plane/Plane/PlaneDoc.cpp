// PlaneDoc.cpp : CPlaneDoc 类的实现
//

#include "stdafx.h"
#include "Plane.h"

#include "PlaneDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneDoc

IMPLEMENT_DYNCREATE(CPlaneDoc, CDocument)

BEGIN_MESSAGE_MAP(CPlaneDoc, CDocument)
END_MESSAGE_MAP()


// CPlaneDoc 构造/析构

CPlaneDoc::CPlaneDoc()
{
    //this->enemyArray.push_back(CEnemy(CPoint(0,0)));
    
}

CPlaneDoc::~CPlaneDoc()
{
}

BOOL CPlaneDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CPlaneDoc 序列化

void CPlaneDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CPlaneDoc 诊断

#ifdef _DEBUG
void CPlaneDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPlaneDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPlaneDoc 命令
