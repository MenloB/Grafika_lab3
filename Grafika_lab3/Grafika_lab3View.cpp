
// Grafika_lab3View.cpp : implementation of the CGrafikalab3View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Grafika_lab3.h"
#endif

#include "Grafika_lab3Doc.h"
#include "Grafika_lab3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGrafikalab3View

IMPLEMENT_DYNCREATE(CGrafikalab3View, CView)

BEGIN_MESSAGE_MAP(CGrafikalab3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGrafikalab3View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CGrafikalab3View construction/destruction

CGrafikalab3View::CGrafikalab3View()
{
	// TODO: add construction code here
}

CGrafikalab3View::~CGrafikalab3View()
{
}

BOOL CGrafikalab3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGrafikalab3View drawing

void CGrafikalab3View::OnDraw(CDC* pDC)
{
	CGrafikalab3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	pDC->SetMapMode(MM_ISOTROPIC);
	CRect rect;
	GetClientRect(&rect);

	pDC->SetWindowExt(1000, 500);
	pDC->SetViewportExt(rect.right, rect.bottom);

	CBitmap ram;
	CBitmap part1, part2, part3, part4;

	BITMAP bm;
	CBitmap mask;


	ram.LoadBitmap(IDB_BITMAP5);
	part1.LoadBitmap(IDB_BITMAP1);
	part2.LoadBitmap(IDB_BITMAP2);
	part3.LoadBitmap(IDB_BITMAP3);
	part4.LoadBitmap(IDB_BITMAP4);

	part1.GetBitmap(&bm);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	/*memDC->SelectObject(&ram);
	pDC->StretchBlt(600, 100, 497, 667, memDC, 0, 0, 1500, 2000, SRCCOPY);*/

	/*DrawPuzzlePart(pDC, 0, 0, 0, IDB_BITMAP1);

	DrawPuzzlePart(pDC, 0, 0, 0, IDB_BITMAP2);*/

	memDC->SelectObject(&ram);

	DrawBitmap(memDC, 750, 100, 1.5, IDB_BITMAP5);

	XFORM XformOld;

	DrawTransparentBitmap(pDC, 10, 10, 10, 1, 1, 1, IDB_BITMAP1);

	/*memDC->SelectObject(&part1);
	pDC->StretchBlt(600, 110, 497, 667, memDC, 0, 0, 1500, 2000, SRCCOPY);*/

	memDC->DeleteDC();
	delete memDC;
}

//Funkcije za 3. lab vezbu
void CGrafikalab3View::SetBitmapTransform(CDC* pdc, float cx, float cy, float bw, float bh, float scale, float alpha, bool mirror, XFORM *oldXform) 
{
	CDC* pDC = GetDC();

	int prevMode = pDC->SetGraphicsMode(GM_ADVANCED);
	BOOL b = pDC->GetWorldTransform(oldXform);
	DWORD dw = GetLastError();
	XFORM newXform;

	if (mirror)
	{
		newXform.eM11 = (FLOAT) -1;
		newXform.eM12 = (FLOAT) 0;
		newXform.eM21 = (FLOAT) 0;
		newXform.eM22 = (FLOAT) 1;
		newXform.eDx =  (FLOAT) -75.0;
		newXform.eDy =  (FLOAT) -75.0;

		b = pDC->SetWorldTransform(&newXform);
		dw = GetLastError();

		pDC->Rectangle(10, 10, 100, 100);

	}

	newXform.eM11 = (FLOAT) 1.0;
	newXform.eM12 = (FLOAT) 0.0;
	newXform.eM21 = (FLOAT) 0.0;
	newXform.eM22 = (FLOAT) 1.0;
	newXform.eDx = (FLOAT) 1.0 + scale;
	newXform.eDy = (FLOAT) 1.0 + scale;

	b = pDC->ModifyWorldTransform(&newXform, MWT_LEFTMULTIPLY);
	dw = GetLastError();

	newXform.eM11 = (FLOAT) cos(alpha);
	newXform.eM11 = (FLOAT) sin(alpha);
	newXform.eM11 = (FLOAT) -sin(alpha);
	newXform.eM11 = (FLOAT) cos(alpha);
	newXform.eM11 = (FLOAT) 0.0;
	newXform.eM11 = (FLOAT) 0.0;

	b = pDC->ModifyWorldTransform(&newXform, MWT_LEFTMULTIPLY);
	dw = GetLastError();

	newXform.eM11 = (FLOAT) 1.0;
	newXform.eM12 = (FLOAT) 0.0;
	newXform.eM21 = (FLOAT) 0.0;
	newXform.eM22 = (FLOAT) 1.0;
	newXform.eDx = (FLOAT) cx;
	newXform.eDy = (FLOAT) cy;

	b = pDC->ModifyWorldTransform(&newXform, MWT_LEFTMULTIPLY);
	dw = GetLastError();

	pDC->SetGraphicsMode(prevMode);
}
void CGrafikalab3View::DrawTransparentBitmap(CDC* pDC, int x, int y, float scale, bool r, bool g, bool b, UINT id)
{
	CBitmap bmp;
	BITMAP bm;
	CBitmap mask;

	bmp.LoadBitmap(id);
	bmp.GetBitmap(&bm);

	mask.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

	CDC* srcDC = new CDC();
	srcDC->CreateCompatibleDC(pDC);
	CDC* dstDC = new CDC();
	dstDC->CreateCompatibleDC(pDC);

	CBitmap* oldSrcBmp = srcDC->SelectObject(&bmp); //originalna bitmapa
	CBitmap* transDstBmp = dstDC->SelectObject(&mask); //maska za maskiranje fluorescentne pozadine

	COLORREF clrBckTopLeft = srcDC->GetPixel(0, 0);
	COLORREF clrSaveBk = srcDC->SetBkColor(clrBckTopLeft);

	dstDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, srcDC, 0, 0, SRCCOPY);

	COLORREF clrSaveText = srcDC->SetTextColor(RGB(255, 255, 255));
	srcDC->SetBkColor(RGB(0, 0, 0));
	srcDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, dstDC, 0, 0, SRCAND);

	dstDC->SetTextColor(clrSaveText);
	srcDC->SetBkColor(clrSaveBk);
	srcDC->SelectObject(oldSrcBmp);
	dstDC->SelectObject(transDstBmp);
	srcDC->DeleteDC();
	delete srcDC;
	dstDC->DeleteDC();
	delete dstDC;

}
void CGrafikalab3View::DrawBitmap(CDC* pDC, int x, int y, float scale, UINT id) {
	CBitmap bmp;
	BITMAP bmpTmp;

	CDC* tmpDC = GetDC();

	bmp.LoadBitmap(id);
	bmp.GetBitmap(&bmpTmp);

	tmpDC->StretchBlt(x, y, bmpTmp.bmWidth, bmpTmp.bmHeight, pDC, 0, 0, 1500 / scale, 2000 / scale, SRCCOPY);
}


//Pomocne funkcije

// CGrafikalab3View printing


void CGrafikalab3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGrafikalab3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGrafikalab3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGrafikalab3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CGrafikalab3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGrafikalab3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGrafikalab3View diagnostics

#ifdef _DEBUG
void CGrafikalab3View::AssertValid() const
{
	CView::AssertValid();
}

void CGrafikalab3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGrafikalab3Doc* CGrafikalab3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGrafikalab3Doc)));
	return (CGrafikalab3Doc*)m_pDocument;
}
#endif //_DEBUG


// CGrafikalab3View message handlers
