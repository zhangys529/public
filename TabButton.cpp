// TabButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "TabButton.h"


// CTabButton

IMPLEMENT_DYNAMIC(CTabButton, CWnd)

CTabButton::CTabButton()
{
	m_cImgCloseBtn.m_hWnd = NULL;
	m_bIsSelected = FALSE;
	m_vecBoundWnd.clear();
}

CTabButton::~CTabButton()
{
	for (int i = 0; i < m_vecBoundWnd.size(); ++i)
	{
		if (m_vecBoundWnd.at(i)->m_hWnd)
		{
			m_vecBoundWnd.at(i)->DestroyWindow();
			delete m_vecBoundWnd.at(i);
			m_vecBoundWnd.at(i) = NULL;
		}
	}
	m_vecBoundWnd.clear();
}


BEGIN_MESSAGE_MAP(CTabButton, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(10001, OnClickedCloseBtn)
END_MESSAGE_MAP()



// CTabButton ��Ϣ�������




BOOL CTabButton::PreCreateWindow(CREATESTRUCT& cs)
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


BOOL CTabButton::Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO:  �ڴ����ר�ô����/����û���

	return CWnd::Create(_T("TabButton"), lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CTabButton::SetImage(HINSTANCE hInstance, UINT uIDResource, LPCTSTR lpType)
{
	// ���ڸ��ı���ͼƬ�����,����ǰ������NULL
	if (!m_cImgButton.IsNull())
	{
		m_cImgButton.Destroy();
	}
	m_cImgButton.LoadFromResource(hInstance, uIDResource, lpType);
}


void CTabButton::SetSelected(BOOL bIsSelected)
{
	if (bIsSelected != m_bIsSelected)
	{
		m_bIsSelected = bIsSelected;
		Invalidate();
	}
}


void CTabButton::SetBoundWnd(CWnd* pWnd)
{
	if (NULL == pWnd) return;
	m_vecBoundWnd.push_back(pWnd);
}


void CTabButton::MoveBoundWnd(int x, int y, int nWidth, int nHeight)
{
	for (int i = 0; i < m_vecBoundWnd.size(); ++i)
	{
		if (m_vecBoundWnd.at(i)->m_hWnd)
		{
			m_vecBoundWnd.at(i)->MoveWindow(x,y,nWidth,nHeight);
		}
	}
}


BOOL CTabButton::GetSelected()
{
	return m_bIsSelected;
}


HWND CTabButton::GetWndCloseBtn()
{
	return m_cImgCloseBtn.m_hWnd;
}


CWnd* CTabButton::GetFirstBoundWnd()
{
	if (m_vecBoundWnd.empty())
		return NULL;
	return m_vecBoundWnd.at(0);
}


int CTabButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	// �����رհ�ť
	if (NULL == m_cImgCloseBtn.m_hWnd)
	{
		CRect rcClose;
		rcClose.left = lpCreateStruct->cx - lpCreateStruct->cy + 1;
		rcClose.right = lpCreateStruct->cx - 1;
		rcClose.top = 1;
		rcClose.bottom = lpCreateStruct->cy - 1;
		m_cImgCloseBtn.Create(_T(""), WS_CHILD | WS_VISIBLE, rcClose, this, 10001);
		m_cImgCloseBtn.SetImage(lpCreateStruct->hInstance, IDB_CLOSEBTN, PNG);
	}

	return 0;
}


void CTabButton::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (m_cImgCloseBtn.m_hWnd)
	{
		m_cImgCloseBtn.MoveWindow(cx - cy + 1, 1, cy - 2, cy - 2);
	}
}


void CTabButton::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	if (m_cImgButton.IsNull()) return;

	CRect rcClient;
	GetClientRect(rcClient);

	// ��ѡ��
	if (m_bIsSelected)
	{
		m_cImgButton.Draw(dc.m_hDC, rcClient, CRect(0, 0, m_cImgButton.GetWidth() * 1 / 4, m_cImgButton.GetHeight()));
		int nIndex = m_vecBoundWnd.size();
		for (int i = 0; i < nIndex; ++i)
		{
			m_vecBoundWnd.at(i)->ShowWindow(SW_SHOW);
		}
	}
	else
	{
		m_cImgButton.Draw(dc.m_hDC, rcClient, CRect(m_cImgButton.GetWidth() * 1 / 4, 0, m_cImgButton.GetWidth() * 1 / 2, m_cImgButton.GetHeight()));
		int nIndex = m_vecBoundWnd.size();
		for (int i = 0; i < nIndex; ++i)
		{
			m_vecBoundWnd.at(i)->ShowWindow(SW_HIDE);
		}
	}

	CString strText;
	GetWindowText(strText);
	if (!strText.IsEmpty())
	{
		CFont font;
		font.CreateFont(17, 0, 0, 0, 550,
			false, false, false,
			GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_SCRIPT,
			_T("΢���ź�"));

		// ��������,����ԭ������
		CFont* pOldFont = dc.SelectObject(&font);
		// ���ñ���ģʽ͸��,����ԭ������ģʽ
		int nOldBkMode = dc.SetBkMode(TRANSPARENT);

		// ˮƽ����|��ֱ����|����|����CRect��Χ������...ʡ��
		dc.DrawText(strText,
			CRect(0, 0, rcClient.Width() - rcClient.Height(), rcClient.Height()),
			DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);

		// ���û�ԭ���ı���ģʽ������
		dc.SetBkMode(nOldBkMode);
		dc.SelectObject(pOldFont);
	}
}


void CTabButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!m_bIsSelected)
	{
		m_bIsSelected = TRUE;
		Invalidate();
	}

	// �����ť��,�򸸴��ڷ��͵����ť����Ϣ
	CWnd* pWndParent = GetParent();
	if (pWndParent)
	{
		WORD wID = GetDlgCtrlID();	// ��ȡ��ǰ��ťID
		// WPARAM���ֽ�Ϊ�ؼ�ID,���ֽ�Ϊ֪ͨ��,LPARAMΪ�ؼ����
		pWndParent->SendMessage(WM_COMMAND, MAKEWPARAM(wID, BN_CLICKED), (LPARAM)m_hWnd);
	}

	CWnd::OnLButtonDown(nFlags, point);
}


void CTabButton::OnClickedCloseBtn()
{
	// �򸸴��ڷ��͵����ť����Ϣ
	CWnd* pWndParent = GetParent();
	if (pWndParent)
	{
		WORD wID = m_cImgCloseBtn.GetDlgCtrlID();	// ��ȡ��ǰ��ťID
		// WPARAM���ֽ�Ϊ�ؼ�ID,���ֽ�Ϊ֪ͨ��,LPARAMΪ�ؼ����
		pWndParent->SendMessage(WM_COMMAND, MAKEWPARAM(wID, BN_CLICKED), (LPARAM)m_cImgCloseBtn.m_hWnd);
	}
}
