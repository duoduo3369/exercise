// PlaneDoc.cpp : CPlaneDoc ���ʵ��
//

#include "stdafx.h"

#include "Plane.h"
#include "Util.h"
#include "PlaneDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneDoc

IMPLEMENT_DYNCREATE(CPlaneDoc, CDocument)

BEGIN_MESSAGE_MAP(CPlaneDoc, CDocument)
END_MESSAGE_MAP()


// CPlaneDoc ����/����

CPlaneDoc::CPlaneDoc()
{   

}

CPlaneDoc::~CPlaneDoc()
{
}

BOOL CPlaneDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CPlaneDoc ���л�

void CPlaneDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CPlaneDoc ���

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


// CPlaneDoc ����
