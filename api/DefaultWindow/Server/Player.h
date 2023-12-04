#pragma once
#include "NetworkManager.h"

class CPlayer
{
private:
	struct m_sPlayerData {
		float posX, posY;
		int hp, coin, score;
	};
	struct m_sReadyData {
		int cookietype;
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
	
	int Get_Coin() { return m_iCoin; };
	void Set_Coin(int _iCoin) { m_iCoin = _iCoin; };
	
	int Get_Score() { return m_iScore; };
	void Set_Score(int _iScore) { m_iScore = _iScore; };
	
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
		Set_OppReadyData(_player.Get_CookieType(), CNetworkManager::Get_Instance()->Get_AllReady());
		retval = send(sock, (char*)&m_sOppreadydata, sizeof(m_sOppreadydata), 0);
		if (retval == SOCKET_ERROR) {
			//err_display("send()");
		}
	}


	void Set_PlayerData() {
		m_iHp = m_splayerdata.hp;
		m_iCoin = m_splayerdata.coin;
		m_iScore = m_splayerdata.score;
		m_fposX = m_splayerdata.posX;
		m_fposY = m_splayerdata.posY;
	}
	void Set_ReadyData(){
		m_iCookieType = m_sreadydata.cookietype;
		m_bClientReady = m_sreadydata.ready;
	}
	void Set_OppReadyData(int _Oppcookietype,bool _Oppready) {
		m_sOppreadydata.cookietype = _Oppcookietype;
		m_sOppreadydata.ready = _Oppready;
	}

private:	
	int m_iClientNum = 0;
	bool m_bClientReady = false;
	int m_iCookieType;
	int m_iHp;
	int m_iCoin;
	int m_iScore;
	float m_fposX;
	float m_fposY;
};