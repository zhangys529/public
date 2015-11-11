#pragma once
#include "atlimage.h"

#define GIF		_T("GIF")
#define BMP		_T("BITMAP")
#define EMF		_T("EMF")
#define WMF		_T("WMF")
#define JPEG	_T("JPEG")
#define PNG		_T("PNG")

class CMyImage :
	public CImage
{
public:
	CMyImage();
	~CMyImage();
	BOOL LoadFromResource(HINSTANCE hInstance, UINT nIDResource, LPCTSTR lpType);
};

