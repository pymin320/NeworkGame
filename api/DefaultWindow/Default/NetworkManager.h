#pragma once

//#include "Common.h"
#include <winsock2.h> // 윈속2 메인 헤더
#include <ws2tcpip.h> // 윈속2 확장 헤더

#include <stdio.h> // printf(), ...
#include "ScoreMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#pragma comment(lib, "ws2_32") // ws2_32.lib 링크
class CNetworkManager
{
private:
	CNetworkManager();
	virtual ~CNetworkManager();

public:
	float Get_OppHp() { return m_fOppHp; }
	void Set_OppHp(float _fOppHp) { m_fOppHp = _fOppHp; }

	float Get_OppMaxHp() { return m_fOppMaxHp; }
	void Set_OppMaxHp(float _fOppMaxHp) { m_fOppMaxHp = _fOppMaxHp; }

	float Get_PlayerHp() { return m_fPlayerHp; }
	void Set_PlayerHp(float _fPlayerHp) { m_fPlayerHp = _fPlayerHp; }

	int Get_OppType() { return m_iOppType; }
	void Set_OppType(int _fOppType) { m_iOppType = _fOppType; }

	int Get_PlayerState() { return m_iPlayerState; }
	void Set_PlayerState(int _iPlayerState) { m_iPlayerState = _iPlayerState; }

	int Get_OppState() { return m_iOppState; }
	void Set_OppState(int _fOppState) { m_iOppState = _fOppState; }

	int Get_CurState() { return m_iCurState; }
	void Set_CurState(int _iCurState) { m_iCurState = _iCurState; }

	int Get_OppCurState() { return m_iOppCurState; }
	void Set_OppCurState(int _fOppCurState) { m_iOppCurState = _fOppCurState; }

	float Get_PlayerPosx() { return m_fPlayerPosx; }
	void Set_PlayerPosx(float _fPlayerPosx) { m_fPlayerPosx = _fPlayerPosx; }

	float Get_PlayerPosy() { return m_fPlayerPosy; }
	void Set_PlayerPosy(float _fPlayerPosy) { m_fPlayerPosy = _fPlayerPosy; }

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
			
			Set_ReadyData(CScoreMgr::Get_CookieType(), m_fPlayerHp, data);
			retval = send(sock, (char*)&m_sreadydata, sizeof(m_sreadydata), 0);
			if (retval == SOCKET_ERROR) {
				//err_display("send()");
			}
		}
	}

	bool Get_AllReady() { return m_bAllReady; }
	void Set_AllReady(bool _bAllReady) { m_bAllReady = _bAllReady; }
	bool Recv_AllReady(SOCKET sock, char data[]) {
		if (!m_bRecvReady) {
			int retval;
			retval = recv(sock, (char*)&m_sOppreadydata, sizeof(m_sOppreadydata), 0);
			if (retval == SOCKET_ERROR) {
				//err_display("recv()");
				return false;
			}
			Set_OppType(m_sOppreadydata.cookietype);
			Set_OppMaxHp(m_sOppreadydata.maxhp);
			Set_AllReady(m_sOppreadydata.ready);
			m_bRecvReady = true;
			return Get_AllReady();
		}
	}

	void Send_PlayerData(SOCKET sock, char data[]) {
		int retval;

		Set_PlayerData(m_fPlayerHp, CScoreMgr::Get_Coin(), CScoreMgr::Get_Score(), m_fPlayerPosx, m_fPlayerPosy ,m_iPlayerState, m_iCurState);
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
		Set_OppCurState(m_sOppplayerdata.curstate);
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
	void Set_PlayerData(int _hp, int _coin, int _score, float _posX, float _posY, int _state, int _curstate) {
		m_splayerdata.hp = _hp;
		m_splayerdata.coin = _coin;
		m_splayerdata.score = _score;
		m_splayerdata.posX = _posX;
		m_splayerdata.posY = _posY;
		m_splayerdata.state = _state;
		m_splayerdata.curstate = _curstate;
	}
	void Set_ReadyData(int _cookietype,int _maxhp, bool _ready) {
		m_sreadydata.cookietype = _cookietype;
		m_sreadydata.maxhp = _maxhp;
		m_sreadydata.ready = _ready;
	}

private:
	struct m_sPlayerData {
		float posX, posY;
		int hp, coin, score, state, curstate;
	};
	//enum STATE { IDLE, WALK, JUMP, DOUBLEJUMP, SLIDE, DEAD, BOOST, GIGA, DEVIL, REVIVE, WITCH, STATE_END };
	struct m_sReadyData {
		int cookietype,maxhp;
		bool ready;
	};
	m_sPlayerData m_splayerdata;
	m_sPlayerData m_sOppplayerdata;
	m_sReadyData m_sreadydata;
	m_sReadyData m_sOppreadydata;

	float m_fOppHp;			//상대 hp
	float m_fOppMaxHp;			//상대 hp
	float m_fPlayerHp;		//내 hp
	int m_iOppType;			//상대 쿠키 타입
	int m_iPlayerState;		//내 상태
	int m_iOppState;		//상대 상태(점프인가 뛰는건가)
	int m_iOppCurState;		//상대 상태 --
	int m_iCurState;		//내 상태 --
	float m_fPlayerPosx;	//내 위치x
	float m_fPlayerPosy;	//내 위치y
	float m_fOppPosx;		//상대 위치x
	float m_fOppPosy;		//상대 위치y
	int m_iOppCoin;			//상대 코인
	int m_iOppScore;		//상대 점수
	bool m_bOppReady = false;		//상대 준비상태
	bool m_bAllReady = false;		//상대,본인 준비 상태
	bool m_bRecvReady = false;
};