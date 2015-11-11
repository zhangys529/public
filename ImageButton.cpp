// ImageButton.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "ImageButton.h"


// CImageButton

IMPLEMENT_DYNAMIC(CImageButton, CWnd)

CImageButton::CImageButton()
{
	m_bIsHover = FALSE;
	m_bIsDown = FALSE;
}

CImageButton::~CImageButton()
{
}


BEGIN_MESSAGE_MAP(CImageButton, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CImageButton 消息处理程序




BOOL CImageButton::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此添加专用代码和/或调用基类
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	if (GetClassInfoEx(cs.hInstance, cs.lpszClass, &wcex))	// 已经注册
	{
		return TRUE;
	}

	// 注册
	wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = AfxWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = cs.hInstance;
	wcex.hIcon = wcex.hIconSm = (HICON)LoadIcon(cs.hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = cs.lpszClass;
	return RegisterClassEx(&wcex);

	//return CWnd::PreCreateWindow(cs);
}


BOOL CImageButton::Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO:  在此添加专用代码和/或调用基类

	return CWnd::Create(_T("IMAGEBUTTON"), lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CImageButton::SetImage(HINSTANCE hInstance, UINT uIDResource, LPCTSTR lpType, UINT uVerticalOrHorizontal)
{
	// 存在更改背景图片的情况,更改前并不是NULL
	if (!m_cImgButton.IsNull())
	{
		m_cImgButton.Destroy();
	}
	m_cImgButton.LoadFromResource(hInstance, uIDResource, lpType);
	m_uVerticalOrHorizontal = uVerticalOrHorizontal;
}


void CImageButton::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	if (m_cImgButton.IsNull()) return;

	CRect rcClient;
	GetClientRect(rcClient);

	// 图片从左到右: 正常状态/经过状态/按下状态/禁用状态
	// 禁用状态
	if (!IsWindowEnabled())
	{
		if (0 == m_uVerticalOrHorizontal)
		{
			m_cImgButton.Draw(dc.m_hDC, rcClient, CRect(m_cImgButton.GetWidth() * 3 / 4, 0, m_cImgButton.GetWidth(), m_cImgButton.GetHeight()));
		}
		else
		{
			m_cImgButton.Draw(dc.m_hDC, rcClient, CRect(0, m_cImgButton.GetHeight() * 3 / 4, m_cImgButton.GetWidth(), m_cImgButton.GetHeight()));
		}
		return;
	}
	// 经过
	if (m_bIsHover)
	{
		// 按下
		if (m_bIsDown)
		{
			if (0 == m_uVerticalOrHorizontal)
			{
				m_cImgButton.Draw(dc.m_hDC, rcClient, CRect(m_cImgButton.GetWidth() * 2 / 4, 0, m_cImgButton.GetWidth() * 3 / 4, m_cImgButton.GetHeight()));
			}
			else
			{
				m_cImgButton.Draw(dc.m_hDC, rcClient, CRect(0, m_cImgButton.GetHeight() * 2 / 4, m_cImgButton.GetWidth(), m_cImgButton.GetHeight() * 3 / 4));
			}
		}
		else
		{
			if (0 == m_uVerticalOrHorizontal)
			{
				m_cImgButton.Draw(dc.m_hDC, rcClient, CRect(m_cImgButton.GetWidth() * 1 / 4, 0, m_cImgButton.GetWidth() * 2 / 4, m_cImgButton.GetHeight()));
			}
			else
			{
				m_cImgButton.Draw(dc.m_hDC, rcClient, CRect(0, m_cImgButton.GetHeight() * 1 / 4, m_cImgButton.GetWidth(), m_cImgButton.GetHeight() * 2 / 4));
			}
		}
	}
	else
	{
		if (0 == m_uVerticalOrHorizontal)
		{
			m_cImgButton.Draw(dc.m_hDC, rcClient, CRect(0, 0, m_cImgButton.GetWidth() * 1 / 4, m_cImgButton.GetHeight()));
		}
		else
		{
			m_cImgButton.Draw(dc.m_hDC, rcClient, CRect(0, 0, m_cImgButton.GetWidth(), m_cImgButton.GetHeight() * 1 / 4));
		}
	}
}


void CImageButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	// 监控鼠标的hover/leave状态,监控到则会对应发送WM_MOUSEHOVER/WM_MOUSELEAVE消息
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.hwndTrack = m_hWnd;
	tme.dwHoverTime = 1;	// 1ms
	TrackMouseEvent(&tme);

	CWnd::OnMouseMove(nFlags, point);
}


void CImageButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (!m_bIsHover)
	{
		m_bIsHover = TRUE;
		Invalidate();	// 重绘
	}

	CWnd::OnMouseHover(nFlags, point);
}


void CImageButton::OnMouseLeave()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_bIsHover)
	{
		m_bIsHover = FALSE;
		Invalidate();	// 重绘
	}

	CWnd::OnMouseLeave();
}


void CImageButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (!m_bIsDown)
	{
		m_bIsDown = TRUE;
		Invalidate();
	}

	CWnd::OnLButtonDown(nFlags, point);
}


void CImageButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonUp(nFlags, point);	// 必须放在函数开始位置,否则有些按钮可能因为发送了关闭消息导致异常
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_bIsDown)
	{
		m_bIsDown = FALSE;
		Invalidate();
	}

	// 点击按钮并松开后,向父窗口发送点击按钮的消息
	CWnd* pWndParent = GetParent();
	if (pWndParent)
	{
		WORD wID = GetDlgCtrlID();	// 获取当前按钮ID
		// WPARAM高字节为控件ID,低字节为通知码,LPARAM为控件句柄
		pWndParent->SendMessage(WM_COMMAND, MAKEWPARAM(wID, BN_CLICKED), (LPARAM)m_hWnd);
	}
}
