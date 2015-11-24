#pragma once
class CNetTraffic
{
private:
	CNetTraffic();
	~CNetTraffic();
	enum ETrafficType			// ��������
	{
		AllTraffic = 388,		// �ܵ�����
		IncomingTraffic = 264,	// ��������
		OutgoingTraffic = 506,	// �������
		Bandwidth = 520			// ����
	};
public:
	BOOL RefreshInterfacesTraffic();						// ˢ�����нӿ�����
	int GetNetworkInterfacesCount();						// �õ��ӿڵ���Ŀ
	CString GetNetworkInterfaceName(int iIndex);			// �õ�index�����ӿڵ�����
	DWORD GetBandwidth(int iIndex);							// �õ�index�����ӿڵĴ���
	DWORD GetIncrementalIncomingTraffic(int iIndex);		// �õ�index�����ӿڵ�������������
	DWORD GetIncrementalOutgoingTraffic(int iIndex);		// �õ�index�����ӿڵ������������
	DWORD GetTotalIncomingTraffic(int iIndex);				// �õ�index�����ӿڵ�����������
	DWORD GetTotalOutgoingTraffic(int iIndex);				// �õ�index�����ӿڵ����������

	static CNetTraffic* create_instance();
private:
	CStringList m_listInterfaces;
	CList<DWORD, DWORD&> m_listBandwidths;					// ����
	CList<DWORD, DWORD&> m_listIncrementalIncomingTraffic;	// ������������
	CList<DWORD, DWORD&> m_listIncrementalOutgoingTraffic;	// �����������
	CList<DWORD, DWORD&> m_listTotalIncomingTraffics;		// ����������
	CList<DWORD, DWORD&> m_listTotalOutgoingTraffics;		// ���������

	static CNetTraffic* m_pInstance;
};

