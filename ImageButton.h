#pragma once
#include "MyImage.h"

// CImageButton

class CImageButton : public CWnd
{
	DECLARE_DYNAMIC(CImageButton)

public:
	CImageButton();
	virtual ~CImageButton();

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	void SetImage(HINSTANCE hInstance, UINT uIDResource, LPCTSTR lpType, UINT uVerticalOrHorizontal = 0);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

private:
	CMyImage m_cImgButton;			// ����ͼƬ
	BOOL m_bIsHover;				// �Ƿ񾭹���ť
	BOOL m_bIsDown;					// �Ƿ��°�ť
	UINT m_uVerticalOrHorizontal;	// ͼ��ˮƽ(0)/��ֱ(1)����
};


