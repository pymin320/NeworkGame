#pragma once

//#include "Common.h"
#include <winsock2.h> // ����2 ���� ���
#include <ws2tcpip.h> // ����2 Ȯ�� ���

#include <stdio.h> // printf(), ...
#include "ScoreMgr.h"
#include "Player.h"
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

	int Get_PlayerState() { return m_iPlayerState; }
	void Set_PlayerState(int _iPlayerState) { m_iPlayerState = _iPlayerState; }

	int Get_OppState() { return m_iOppState; }
	void Set_OppState(int _fOppState) { m_iOppState = _fOppState; }

	float Get_PlayerPosx() { return m_fPlayerPosx; }
	void Set_PlayerPosx(float _fPlayerPosx) { m_fPlayerPosx = _fPlayerPosx; }

	float Get_PlayerPosy() { return m_fPlayerPosy; }
	void Set_PlayerPosy(float _fPlayerPosy) { m_fPlayerPosy = _fPlayerPosy; }

	bool Get_PlayerCollide() { return m_bPlayerCollide; }
	void Set_PlayerCollide(bool _bPlayerCollide) { m_bPlayerCollide = _bPlayerCollide; }

	float Get_OppPosx() { return m_fOppPosx; }
	void Set_OppPosx(float _fOppPosx) { m_fOppPosx = _fOppPosx; }

	float Get_OppPosy() { return m_fOppPosy; }
	void Set_OppPosy(float _fOppPosy) { m_fOppPosy = _fOppPosy; }

	int Get_OppCoin() { return m_iOppCoin; }
	void Set_OppCoin(int _iOppCOin) { m_iOppCoin = _iOppCOin; }

	int Get_OppScore() { return m_iOppScore; }
	void Set_OppScore(int _iOppScore) { m_iOppScore = _iOppScore; }

	bool Get_OppReady() { return m_bOppReady; }
	void Set_OppReady(bool _bOppReady) { m_bOppReady = _bOppReady; }
	void Send_OppReady(SOCKET sock, bool data) {
		if (!Get_AllReady()) {
			int retval;
			
			Set_ReadyData(CScoreMgr::Get_CookieType(), data);
			retval = send(sock, (char*)&m_sreadydata, sizeof(m_sreadydata), 0);
			if (retval == SOCKET_ERROR) {
				//err_display("send()");
			}
		}
	}

	bool Get_AllReady() { return m_bAllReady; }
	void Set_AllReady(bool _bAllReady) { m_bAllReady = _bAllReady; }
	bool Recv_AllReady(SOCKET sock, char data[]) {
		int retval;
		retval = recv(sock, (char*)&m_sOppreadydata, sizeof(m_sOppreadydata), 0);
		if (retval == SOCKET_ERROR) {
			//err_display("recv()");
			return false;
		}
		Set_OppType(m_sOppreadydata.cookietype);
		Set_AllReady(m_sOppreadydata.ready);
		return Get_AllReady();
	}

	void Send_PlayerData(SOCKET sock, char data[]) {
		int retval;

		Set_PlayerData(m_fPlayerHp, CScoreMgr::Get_Coin(), CScoreMgr::Get_Score(), m_fPlayerPosx, m_fPlayerPosy ,m_iPlayerState, m_bPlayerCollide);
		retval = send(sock, (char*)&m_splayerdata, sizeof(m_splayerdata), 0);
		if (retval == SOCKET_ERROR) {
			//err_display("send()");
		}
	}

	void Recv_OppPlayerData(SOCKET sock, char data[]) {
		int retval;

		retval = recv(sock, (char*)&m_sOppplayerdata, sizeof(m_sOppplayerdata), 0);
		if (retval == SOCKET_ERROR) {
			//err_display("send()");
		}
		Set_OppHp(m_sOppplayerdata.hp);
		Set_OppCoin(m_sOppplayerdata.coin);
		Set_OppScore(m_sOppplayerdata.score);
		Set_OppPosx(m_sOppplayerdata.posX);
		Set_OppPosy(m_sOppplayerdata.posY);
		Set_OppState(m_sOppplayerdata.state);
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
	void Set_PlayerData(int _hp, int _coin, int _score, float _posX, float _posY, int _state, bool _collide) {
		m_splayerdata.hp = _hp;
		m_splayerdata.coin = _coin;
		m_splayerdata.score = _score;
		m_splayerdata.posX = _posX;
		m_splayerdata.posY = _posY;
		m_splayerdata.state = _state;
		m_splayerdata.collide = _collide;
	}
	void Set_ReadyData(int _cookietype, bool _ready) {
		m_sreadydata.cookietype = _cookietype;
		m_sreadydata.ready = _ready;
	}

private:
	struct m_sPlayerData {
		float posX, posY;
		int hp, coin, score, state;
		bool collide;
	};
	//enum STATE { IDLE, WALK, JUMP, DOUBLEJUMP, SLIDE, DEAD, BOOST, GIGA, DEVIL, REVIVE, WITCH, STATE_END };
	struct m_sReadyData {
		int cookietype;
		bool ready;
	};
	m_sPlayerData m_splayerdata;
	m_sPlayerData m_sOppplayerdata;
	m_sReadyData m_sreadydata;
	m_sReadyData m_sOppreadydata;

	float m_fOppHp;					//��� hp
	float m_fPlayerHp;				//�� hp
	int m_iOppType;					//��� ��Ű Ÿ��
	int m_iPlayerState;				//�� ����
	int m_iOppState;				//��� ����(�����ΰ� �ٴ°ǰ�)
	float m_fPlayerPosx;			//�� ��ġx
	float m_fPlayerPosy;			//�� ��ġy
	bool m_bPlayerCollide = false;	//�浹 üũ

	float m_fOppPosx;				//��� ��ġx
	float m_fOppPosy;				//��� ��ġy
	int m_iOppCoin;					//��� ����
	int m_iOppScore;				//��� ����
	bool m_bOppReady = false;		//��� �غ����
	bool m_bAllReady = false;		//���,���� �غ� ����
};