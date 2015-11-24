#include "stdafx.h"
#include "NetTraffic.h"
#include "PerfInterface.h"

CNetTraffic* CNetTraffic::m_pInstance = NULL;

CNetTraffic::CNetTraffic()
{
	m_listInterfaces.RemoveAll();
	m_listBandwidths.RemoveAll();
	m_listIncrementalIncomingTraffic.RemoveAll();
	m_listIncrementalOutgoingTraffic.RemoveAll();
	m_listTotalIncomingTraffics.RemoveAll();
	m_listTotalOutgoingTraffics.RemoveAll();
}


CNetTraffic::~CNetTraffic()
{
}

BOOL CNetTraffic::RefreshInterfacesTraffic()
{
	try
	{
		PERF_DATA_BLOCK* pDataBlock = GetDataBlock("510");			// �õ����ݿ�
		PERF_OBJECT_TYPE* pObjectType = FirstObject(pDataBlock);	// �õ���һ������
		int a = 0;
		for (; a < pDataBlock->NumObjectTypes; ++a)
		{
			if (pObjectType->ObjectNameTitleIndex == 510)			// �ж��Ƿ����������(������510)
			{
				break;
			}
			pObjectType = NextObject(pObjectType);					// ��һ������
		}
		if (a == pDataBlock->NumObjectTypes)						// û���������
		{
			delete[] pDataBlock;
			return FALSE;
		}
		PERF_INSTANCE_DEFINITION* pInstance = FirstInstance(pObjectType);
		char szNameBuffer[255];
		for (int b = 0; b < pObjectType->NumInstances; ++b)
		{
			wchar_t* pSrcName = (wchar_t*)((BYTE*)pInstance + pInstance->NameOffset);
			char* pName = WideToMulti(pSrcName, szNameBuffer, sizeof(szNameBuffer));
			PERF_COUNTER_BLOCK* pCounterBlock = GetCounterBlock(pInstance);
			// ����
			DWORD ulBandwithOffset = GetCounterOffset(pObjectType, ETrafficType::Bandwidth);
			DWORD ulBandwith = *((DWORD*)((BYTE*)pCounterBlock + ulBandwithOffset));
			// ��������
			DWORD ulIncomingTrafficOffset = GetCounterOffset(pObjectType, ETrafficType::IncomingTraffic);
			DWORD ulIncomingTraffic = *((DWORD*)((BYTE*)pCounterBlock + ulIncomingTrafficOffset));
			// �������
			DWORD ulOutgoingTrafficOffset = GetCounterOffset(pObjectType, ETrafficType::OutgoingTraffic);
			DWORD ulOutgoingTraffic = *((DWORD*)((BYTE*)pCounterBlock + ulOutgoingTrafficOffset));

			// ͨ���ӿ����һ�������, ����Ҳ���������, ���ҵ����������������
			POSITION pos = m_listInterfaces.Find(pName);
			if (NULL == pos)
			{
				m_listInterfaces.AddTail(CString(pName));
				m_listBandwidths.AddTail(ulBandwith);
				m_listIncrementalIncomingTraffic.AddTail(0);
				m_listIncrementalOutgoingTraffic.AddTail(0);
				m_listTotalIncomingTraffics.AddTail(ulIncomingTraffic);
				m_listTotalOutgoingTraffics.AddTail(ulOutgoingTraffic);
			}
			else
			{
				DWORD ulIncrementalIncomingTraffic = ulIncomingTraffic - m_listTotalIncomingTraffics.GetAt(pos);
				DWORD ulIncrementalOutgoingTraffic = ulOutgoingTraffic - m_listTotalOutgoingTraffics.GetAt(pos);
				m_listBandwidths.SetAt(pos, ulBandwith);
				m_listIncrementalIncomingTraffic.SetAt(pos, ulIncrementalIncomingTraffic);
				m_listIncrementalOutgoingTraffic.SetAt(pos, ulIncrementalOutgoingTraffic);
				m_listTotalIncomingTraffics.AddTail(ulIncomingTraffic);
				m_listTotalOutgoingTraffics.AddTail(ulOutgoingTraffic);
			}

			pInstance = NextInstance(pInstance);
		}
		delete[] pDataBlock;
		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
}
int CNetTraffic::GetNetworkInterfacesCount()
{
	return m_listInterfaces.GetCount();
}
CString CNetTraffic::GetNetworkInterfaceName(int iIndex)
{
	POSITION pos = m_listInterfaces.FindIndex(iIndex);
	if (NULL == pos)
	{
		return FALSE;
	}
	return m_listInterfaces.GetAt(pos);
}
DWORD CNetTraffic::GetBandwidth(int iIndex)
{
	POSITION pos = m_listBandwidths.FindIndex(iIndex);
	if (NULL == pos)
	{
		return 0;
	}
	return m_listBandwidths.GetAt(pos);
}
DWORD CNetTraffic::GetIncrementalIncomingTraffic(int iIndex)
{
	POSITION pos = m_listIncrementalIncomingTraffic.FindIndex(iIndex);
	if (NULL == pos)
	{
		return 0;
	}
	return m_listIncrementalIncomingTraffic.GetAt(pos);
}
DWORD CNetTraffic::GetIncrementalOutgoingTraffic(int iIndex)
{
	POSITION pos = m_listIncrementalOutgoingTraffic.FindIndex(iIndex);
	if (NULL == pos)
	{
		return 0;
	}
	return m_listIncrementalOutgoingTraffic.GetAt(pos);
}
DWORD CNetTraffic::GetTotalIncomingTraffic(int iIndex)
{
	POSITION pos = m_listTotalIncomingTraffics.FindIndex(iIndex);
	if (NULL == pos)
	{
		return 0;
	}
	return m_listTotalIncomingTraffics.GetAt(pos);
}
DWORD CNetTraffic::GetTotalOutgoingTraffic(int iIndex)
{
	POSITION pos = m_listTotalOutgoingTraffics.FindIndex(iIndex);
	if (NULL == pos)
	{
		return 0;
	}
	return m_listTotalOutgoingTraffics.GetAt(pos);
}

CNetTraffic* CNetTraffic::create_instance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CNetTraffic();
	}
	return m_pInstance;
}