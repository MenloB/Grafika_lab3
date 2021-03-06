
// Grafika_lab3View.h : interface of the CGrafikalab3View class
//

#pragma once


class CGrafikalab3View : public CView
{
protected: // create from serialization only
	CGrafikalab3View();
	DECLARE_DYNCREATE(CGrafikalab3View)

// Attributes
public:
	CGrafikalab3Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view

	virtual void DrawTransparentBitmap(CDC* pDC, int x, int y, float scale, bool r, bool g, bool b, UINT id);
	virtual void DrawBitmap(CDC* pDC, int x, int y, float scale, UINT name);
	virtual void SetBitmapTransform(CDC* pDC, float cx, float cy, float bw, float bh, float scale, float alpha, bool mirror, XFORM *oldXform);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGrafikalab3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_r = true;
	BOOL m_g = true;
	BOOL m_b = true;
};

#ifndef _DEBUG  // debug version in Grafika_lab3View.cpp
inline CGrafikalab3Doc* CGrafikalab3View::GetDocument() const
   { return reinterpret_cast<CGrafikalab3Doc*>(m_pDocument); }
#endif

