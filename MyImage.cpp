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

	// ������Դ
	HRSRC hRsrc = FindResource(hInstance, MAKEINTRESOURCE(nIDResource), lpType);
	if (NULL == hRsrc) return FALSE;

	// ������Դ
	HGLOBAL hImgData = LoadResource(hInstance, hRsrc);
	if (NULL == hImgData)
	{
		FreeResource(hImgData);
		return FALSE;
	}

	// �����ڴ��е�ָ����Դ
	LPVOID lpVoid = LockResource(hImgData);
	LPSTREAM pStream = NULL;
	DWORD dwSize = SizeofResource(hInstance, hRsrc);
	HGLOBAL hMem = GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)GlobalLock(hMem);
	memcpy(lpByte, lpVoid, dwSize);

	// ����ڴ��е�ָ����Դ
	GlobalUnlock(hMem);

	// ��ָ���ڴ洴��������
	HRESULT ht = CreateStreamOnHGlobal(hMem, TRUE, &pStream);
	if (ht != S_OK)
	{
		GlobalFree(hMem);
	}
	else
	{
		// ����ͼƬ
		Load(pStream);

		GlobalFree(hMem);
	}

	// �ͷ���Դ
	FreeResource(hImgData);

	return TRUE;
}
