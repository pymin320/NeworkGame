#pragma once

//#include "Common.h"
#include <winsock2.h> // ����2 ���� ���
#include <ws2tcpip.h> // ����2 Ȯ�� ���

#include <stdio.h> // printf(), ...
#include "ScoreMgr.h"
#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ
class CNetworkManager
{
private:
	CNetworkManager();
	virtual ~CNetworkManager();

public:
	float Get_OppHp() { return m_fOppHp; }
	void Set_OppHp(float _fOppHp) { m_fOppHp = _fOppHp; }

	float Get_PlayerHp() { return m_fPlayerHp; }
	void Set_PlayerHp(float _fPlayerHp) { m_fPlayerHp = _fPlayerHp; }

	int Get_OppType() { return m_iOppType; }
	void Set_OppType(int _fOppType) { m_iOppType = _fOppType; }

	int Get_OppState() { return m_iOppState; }
	void Set_OppState(int _fOppState) { m_iOppState = _fOppState; }

	float Get_OppPosx() { return m_fOppPosx; }
	void Set_OppPosx(float _fOppPosx) { m_fOppPosx = _fOppPosx; }

	float Get_OppPosy() { return m_fOppPosy; }
	void Set_OppPosy(float _fOppPosy) { m_fOppPosy = _fOppPosy; }

	bool Get_OppReady() { return m_bOppReady; }
	void Set_OppReady(bool _bOppReady) { m_bOppReady = _bOppReady; }
	void Send_OppReady(SOCKET sock, bool data) {
		if (!Get_AllReady()) {
			int retval;
			retval = send(sock, (char*)&data, sizeof(bool), 0);
			if (retval == SOCKET_ERROR) {
				//err_display("send()");
			}
		}
	}

	bool Get_AllReady() { return m_bAllReady; }
	void Set_AllReady(bool _bAllReady) { m_bAllReady = _bAllReady; }
	bool Recv_AllReady(SOCKET sock, char data[]) {
		int retval;
		retval = recv(sock, data, sizeof(bool), 0);
		if (retval == SOCKET_ERROR) {
			//err_display("recv()");
			return false;
		}
		return (bool)data[0];
	}

	void Send_PlayerData(SOCKET sock, char data[],size_t datasize) {
		int retval;

		Set_PlayerData(m_fPlayerHp, CScoreMgr::Get_Coin(), CScoreMgr::Get_Score());
		retval = send(sock, (char*)&m_splayerdata, sizeof(m_splayerdata), 0);
		if (retval == SOCKET_ERROR) {
			//err_display("send()");
		}
	}
	


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
	void Set_PlayerData(int _hp, int _coin, int _score) {
		m_splayerdata.hp = _hp;
		m_splayerdata.coin = _coin;
		m_splayerdata.score = _score;
	}

private:
	struct m_sPlayerData {
		int hp, coin, score;
	};
	m_sPlayerData m_splayerdata;


	float m_fOppHp;			//��� hp
	float m_fPlayerHp;		//�� hp
	int m_iOppType;			//��� ��Ű Ÿ��
	int m_iOppState;		//��� ����(�����ΰ� �ٴ°ǰ�)
	float m_fOppPosx;		//��� ��ġx
	float m_fOppPosy;		//��� ��ġy
	bool m_bOppReady = false;		//��� �غ����
	bool m_bAllReady = false;		//���,���� �غ� ����
};

