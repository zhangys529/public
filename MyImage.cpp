#include "stdafx.h"
#include "MyImage.h"


CMyImage::CMyImage()
{
}


CMyImage::~CMyImage()
{
}


BOOL CMyImage::LoadFromResource(HINSTANCE hInstance, UINT nIDResource, LPCTSTR lpType)
{
	if (NULL == this) return FALSE;
	Destroy();

	// 查找资源
	HRSRC hRsrc = FindResource(hInstance, MAKEINTRESOURCE(nIDResource), lpType);
	if (NULL == hRsrc) return FALSE;

	// 加载资源
	HGLOBAL hImgData = LoadResource(hInstance, hRsrc);
	if (NULL == hImgData)
	{
		FreeResource(hImgData);
		return FALSE;
	}

	// 锁定内存中的指定资源
	LPVOID lpVoid = LockResource(hImgData);
	LPSTREAM pStream = NULL;
	DWORD dwSize = SizeofResource(hInstance, hRsrc);
	HGLOBAL hMem = GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)GlobalLock(hMem);
	memcpy(lpByte, lpVoid, dwSize);

	// 解除内存中的指定资源
	GlobalUnlock(hMem);

	// 从指定内存创建流对象
	HRESULT ht = CreateStreamOnHGlobal(hMem, TRUE, &pStream);
	if (ht != S_OK)
	{
		GlobalFree(hMem);
	}
	else
	{
		// 加载图片
		Load(pStream);

		GlobalFree(hMem);
	}

	// 释放资源
	FreeResource(hImgData);

	return TRUE;
}
