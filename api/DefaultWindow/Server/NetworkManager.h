#pragma once


class CNetworkManager
{
private:
	CNetworkManager();
	virtual ~CNetworkManager();

public:
	bool Get_AllReady() { return m_bAllReady; };
	void Set_AllReady(bool _bAllReady) { m_bAllReady = _bAllReady; }

public:
	static		CNetworkManager* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CNetworkManager;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CNetworkManager* m_pInstance;

private:
	bool m_bAllReady = false;
};
