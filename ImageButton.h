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
	CMyImage m_cImgButton;			// 背景图片
	BOOL m_bIsHover;				// 是否经过按钮
	BOOL m_bIsDown;					// 是否按下按钮
	UINT m_uVerticalOrHorizontal;	// 图标水平(0)/竖直(1)布局
};


