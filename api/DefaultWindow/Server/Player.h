#pragma once
#include "NetworkManager.h"

class CPlayer
{
private:
	struct m_sPlayerData {
		float posX, posY;
		int hp, coin, score, state, curstate;
	};  
	struct m_sReadyData {
		int cookietype, maxhp;
		bool ready;
	};
public:
	m_sPlayerData m_splayerdata;
	m_sReadyData m_sreadydata;
	m_sReadyData m_sOppreadydata;
public:
	CPlayer();
	virtual ~CPlayer();

public:
	int Get_ClientNum() { return m_iClientNum; };
	void Set_ClientNum(int _ClientNum) { m_iClientNum = _ClientNum; };
	
	bool Get_PlayerReady() { return m_bClientReady; };
	void Set_PlayerReady(bool _bClientReady) { m_bClientReady = _bClientReady; };
	
	int Get_CookieType() { return m_iCookieType; };
	void Set_CookieType(int _iCookieType) {m_iCookieType = _iCookieType;};
	
	int Get_Hp() { return m_iHp; };
	void Set_Hp(int _iHp) { m_iHp = _iHp; };
	
	int Get_MaxHp() { return m_iMaxHp; };
	void Set_MaxHp(int _iMaxHp) { m_iMaxHp = _iMaxHp; };

	int Get_Coin() { return m_iCoin; };
	void Set_Coin(int _iCoin) { m_iCoin = _iCoin; };
	
	int Get_Score() { return m_iScore; };
	void Set_Score(int _iScore) { m_iScore = _iScore; };
	
	int Get_State() { return m_iState; };
	void Set_State(int _iState) { m_iState = _iState; };
	//enum STATE { IDLE, WALK, JUMP, DOUBLEJUMP, SLIDE, DEAD, BOOST, GIGA, DEVIL, REVIVE, WITCH, STATE_END };

	int Get_CurState() { return m_iCurState; };
	void Set_CurState(int _iCurState) { m_iCurState = _iCurState; };

	float Get_Posx() { return m_fposX; }
	void Set_Posx(float _fposX) { m_fposX = _fposX; }

	float Get_Posy() { return m_fposY; }
	void Set_Posy(float _fposY) { m_fposY = _fposY; }
	bool Recv_ReadyData(SOCKET sock) {
		int retval;
		retval = recv(sock, (char*)&m_sreadydata, sizeof(m_sreadydata), 0);
		if (retval == SOCKET_ERROR) {
			//err_display("recv()");
		}
		Set_ReadyData();
		return Get_PlayerReady();
	}

	void Send_ReadyData(SOCKET sock, CPlayer& _player){
		int retval;
		Set_OppReadyData(_player.Get_CookieType(), _player.Get_MaxHp(), CNetworkManager::Get_Instance()->Get_AllReady());
		retval = send(sock, (char*)&m_sOppreadydata, sizeof(m_sOppreadydata), 0);
		if (retval == SOCKET_ERROR) {
			//err_display("send()");
		}
	}


	void Set_PlayerData() {
		m_fposX = m_splayerdata.posX;
		m_fposY = m_splayerdata.posY;
		m_iHp = m_splayerdata.hp;
		m_iCoin = m_splayerdata.coin;
		m_iScore = m_splayerdata.score;
		m_iState = m_splayerdata.state;
		m_iCurState = m_splayerdata.curstate;
	}
	void Set_ReadyData(){
		m_iCookieType = m_sreadydata.cookietype;
		m_iMaxHp = m_sreadydata.maxhp;
		m_bClientReady = m_sreadydata.ready;
	}
	void Set_OppReadyData(int _Oppcookietype, int _OppMaxHp, bool _Oppready) {
		m_sOppreadydata.cookietype = _Oppcookietype;
		m_sOppreadydata.maxhp = _OppMaxHp;
		m_sOppreadydata.ready = _Oppready;
	}

private:	
	int m_iClientNum = 0;
	int m_iMaxHp;
	bool m_bClientReady = false;
	int m_iCookieType;
	int m_iState;
	int m_iCurState;
	int m_iHp;
	int m_iCoin;
	int m_iScore;
	float m_fposX;
	float m_fposY;
};