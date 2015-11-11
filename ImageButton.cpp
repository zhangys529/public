// ImageButton.cpp : ʵ���ļ�
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



// CImageButton ��Ϣ�������




BOOL CImageButton::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ����ר�ô����/����û���
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	if (GetClassInfoEx(cs.hInstance, cs.lpszClass, &wcex))	// �Ѿ�ע��
	{
		return TRUE;
	}

	// ע��
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
	// TODO:  �ڴ����ר�ô����/����û���

	return CWnd::Create(_T("IMAGEBUTTON"), lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CImageButton::SetImage(HINSTANCE hInstance, UINT uIDResource, LPCTSTR lpType, UINT uVerticalOrHorizontal)
{
	// ���ڸ��ı���ͼƬ�����,����ǰ������NULL
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
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	if (m_cImgButton.IsNull()) return;

	CRect rcClient;
	GetClientRect(rcClient);

	// ͼƬ������: ����״̬/����״̬/����״̬/����״̬
	// ����״̬
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
	// ����
	if (m_bIsHover)
	{
		// ����
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// �������hover/leave״̬,��ص�����Ӧ����WM_MOUSEHOVER/WM_MOUSELEAVE��Ϣ
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!m_bIsHover)
	{
		m_bIsHover = TRUE;
		Invalidate();	// �ػ�
	}

	CWnd::OnMouseHover(nFlags, point);
}


void CImageButton::OnMouseLeave()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_bIsHover)
	{
		m_bIsHover = FALSE;
		Invalidate();	// �ػ�
	}

	CWnd::OnMouseLeave();
}


void CImageButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!m_bIsDown)
	{
		m_bIsDown = TRUE;
		Invalidate();
	}

	CWnd::OnLButtonDown(nFlags, point);
}


void CImageButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonUp(nFlags, point);	// ������ں�����ʼλ��,������Щ��ť������Ϊ�����˹ر���Ϣ�����쳣
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_bIsDown)
	{
		m_bIsDown = FALSE;
		Invalidate();
	}

	// �����ť���ɿ���,�򸸴��ڷ��͵����ť����Ϣ
	CWnd* pWndParent = GetParent();
	if (pWndParent)
	{
		WORD wID = GetDlgCtrlID();	// ��ȡ��ǰ��ťID
		// WPARAM���ֽ�Ϊ�ؼ�ID,���ֽ�Ϊ֪ͨ��,LPARAMΪ�ؼ����
		pWndParent->SendMessage(WM_COMMAND, MAKEWPARAM(wID, BN_CLICKED), (LPARAM)m_hWnd);
	}
}
