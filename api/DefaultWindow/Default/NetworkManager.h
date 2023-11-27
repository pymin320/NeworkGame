#pragma once

class CNetworkManager
{
private:
	CNetworkManager();
	virtual ~CNetworkManager();

public:
	float Get_OppHp() { return m_fOppHp; }
	void Set_OppHp(float _fOppHp) { m_fOppHp = _fOppHp; }

	int Get_OppType() { return m_iOppType; }
	void Set_OppType(int _fOppType) { m_iOppType = _fOppType; }

	int Get_OppState() { return m_iOppState; }
	void Set_OppState(int _fOppState) { m_iOppState = _fOppState; }

	float Get_OppPosx() { return m_fOppPosx; }
	void Set_OppPosx(float _fOppPosx) { m_fOppPosx = _fOppPosx; }

	float Get_OppPosy() { return m_fOppPosy; }
	void Set_OppPosy(float _fOppPosy) { m_fOppPosy = _fOppPosy; }

	bool Get_OppReady() { return m_fOppPosy; }
	void Set_OppReady(bool _bOppReady) { m_fOppPosy = _bOppReady; }



public:
	static		CNetworkManager*		Get_Instance(void)
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
	static CNetworkManager*			m_pInstance;

private:
	float m_fOppHp;			//상대 hp
	int m_iOppType;			//상대 쿠키 타입
	int m_iOppState;		//상대 상태(점프인가 뛰는건가)
	float m_fOppPosx;		//상대 위치x
	float m_fOppPosy;		//상대 위치y
	bool m_bOppReady = false;		//상대 준비상태
};

