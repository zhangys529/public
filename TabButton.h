#pragma once
#include <vector>
#include "MyImage.h"
#include "ImageButton.h"
using namespace std;

// CTabButton

class CTabButton : public CWnd
{
	DECLARE_DYNAMIC(CTabButton)

public:
	CTabButton();
	virtual ~CTabButton();

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	void SetImage(HINSTANCE hInstance, UINT uIDResource, LPCTSTR lpType);
	void SetSelected(BOOL bIsSelected);
	void SetBoundWnd(CWnd* pWnd);
	void MoveBoundWnd(int x, int y, int nWidth, int nHeight);
	BOOL GetSelected();
	HWND GetWndCloseBtn();
	CWnd* GetFirstBoundWnd();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClickedCloseBtn();

private:
	CMyImage m_cImgButton;			// 背景图片
	CImageButton m_cImgCloseBtn;	// 关闭按钮
	vector<CWnd*> m_vecBoundWnd;	// 当前关联的控件列表
	BOOL m_bIsSelected;				// 是否被选中
};


