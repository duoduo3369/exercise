// PlaneView.h : CPlaneView 类的接口
//

#pragma once


class CPlaneView : public CView
{
protected: // 仅从序列化创建
	CPlaneView();
	DECLARE_DYNCREATE(CPlaneView)

// 属性
public:
	CPlaneDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CPlaneView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
//    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//    virtual void OnInitialUpdate();
protected:
//    virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
//    afx_msg void OnTimer(UINT_PTR nIDEvent);
//    afx_msg void OnDestroy();
//    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnDestroy();
    virtual void OnInitialUpdate();
    CDC* pdc;
//    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    CDC* m_pMemDC;
    CBitmap* m_pMemBitmap;
    CBitmap* m_pOldBitmap;
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    unsigned int count_sepcial;
};

#ifndef _DEBUG  // PlaneView.cpp 中的调试版本
inline CPlaneDoc* CPlaneView::GetDocument() const
   { return reinterpret_cast<CPlaneDoc*>(m_pDocument); }
#endif

