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
	CMyImage m_cImgButton;			// ����ͼƬ
	CImageButton m_cImgCloseBtn;	// �رհ�ť
	vector<CWnd*> m_vecBoundWnd;	// ��ǰ�����Ŀؼ��б�
	BOOL m_bIsSelected;				// �Ƿ�ѡ��
};


