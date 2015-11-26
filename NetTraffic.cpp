#include "stdafx.h"
#include "NetTraffic.h"
#include "PerfInterface.h"

CNetTraffic* CNetTraffic::m_pInstance = NULL;

CNetTraffic::CNetTraffic()
{
	m_listInterfaces.RemoveAll();
	m_mapBandwidths.clear();
	m_mapIncrementalIncomingTraffic.clear();
	m_mapIncrementalOutgoingTraffic.clear();
	m_mapTotalIncomingTraffics.clear();
	m_mapTotalOutgoingTraffics.clear();
}


CNetTraffic::~CNetTraffic()
{
}

BOOL CNetTraffic::RefreshInterfacesTraffic()
{
	try
	{
		PERF_DATA_BLOCK* pDataBlock = GetDataBlock(_T("510"));			// �õ����ݿ�
		PERF_OBJECT_TYPE* pObjectType = FirstObject(pDataBlock);	// �õ���һ������
		DWORD a = 0;
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
		for (LONG b = 0; b < pObjectType->NumInstances; ++b)
		{
			wchar_t* pSrcName = (wchar_t*)((BYTE*)pInstance + pInstance->NameOffset);
			CString strName = WideToMulti(pSrcName, szNameBuffer, sizeof(szNameBuffer));
			PERF_COUNTER_BLOCK* pCounterBlock = GetCounterBlock(pInstance);
			// ����
			DWORD dwBandwithOffset = GetCounterOffset(pObjectType, ETrafficType::Bandwidth);
			DWORD dwBandwith = *((DWORD*)((BYTE*)pCounterBlock + dwBandwithOffset));
			// ��������
			DWORD dwIncomingTrafficOffset = GetCounterOffset(pObjectType, ETrafficType::IncomingTraffic);
			DWORD dwIncomingTraffic = *((DWORD*)((BYTE*)pCounterBlock + dwIncomingTrafficOffset));
			// �������
			DWORD dwOutgoingTrafficOffset = GetCounterOffset(pObjectType, ETrafficType::OutgoingTraffic);
			DWORD dwOutgoingTraffic = *((DWORD*)((BYTE*)pCounterBlock + dwOutgoingTrafficOffset));
			// ��������
			DWORD dwIncrementalIncomingTraffic = 0;
			DWORD dwIncrementalOutgoingTraffic = 0;

			// ͨ���ӿ����һ�������, ����Ҳ���������, ���ҵ����������������
			POSITION pos = m_listInterfaces.Find(strName);
			if (NULL == pos)
			{
				m_listInterfaces.AddTail(strName);
			}
			else
			{
				dwIncrementalIncomingTraffic = dwIncomingTraffic - m_mapTotalIncomingTraffics[strName];
				dwIncrementalOutgoingTraffic = dwOutgoingTraffic - m_mapTotalOutgoingTraffics[strName];
			}
			m_mapBandwidths[strName] = dwBandwith;
			m_mapIncrementalIncomingTraffic[strName] = dwIncrementalIncomingTraffic;
			m_mapIncrementalOutgoingTraffic[strName] = dwIncrementalOutgoingTraffic;
			m_mapTotalIncomingTraffics[strName] = dwIncomingTraffic;
			m_mapTotalOutgoingTraffics[strName] = dwOutgoingTraffic;

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
		return _T("");
	}
	return m_listInterfaces.GetAt(pos);
}
DWORD CNetTraffic::GetBandwidth(int iIndex)
{
	CString strName = GetNetworkInterfaceName(iIndex);
	if ("" == strName)
	{
		return 0;
	}
	return m_mapBandwidths[strName];
}
DWORD CNetTraffic::GetIncrementalIncomingTraffic(int iIndex)
{
	CString strName = GetNetworkInterfaceName(iIndex);
	if ("" == strName)
	{
		return 0;
	}
	return m_mapIncrementalIncomingTraffic[strName];
}
DWORD CNetTraffic::GetIncrementalOutgoingTraffic(int iIndex)
{
	CString strName = GetNetworkInterfaceName(iIndex);
	if ("" == strName)
	{
		return 0;
	}
	return m_mapIncrementalOutgoingTraffic[strName];
}
DWORD CNetTraffic::GetTotalIncomingTraffic(int iIndex)
{
	CString strName = GetNetworkInterfaceName(iIndex);
	if ("" == strName)
	{
		return 0;
	}
	return m_mapTotalIncomingTraffics[strName];
}
DWORD CNetTraffic::GetTotalOutgoingTraffic(int iIndex)
{
	CString strName = GetNetworkInterfaceName(iIndex);
	if ("" == strName)
	{
		return 0;
	}
	return m_mapTotalOutgoingTraffics[strName];
}

CNetTraffic* CNetTraffic::create_instance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CNetTraffic();
	}
	return m_pInstance;
}