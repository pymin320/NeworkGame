#pragma once

class CPlayer
{
private:
	struct m_sPlayerData {
		int hp, coin, score, posx, posy;
	};
public:
	m_sPlayerData m_splayerdata;

public:
	CPlayer();
	virtual ~CPlayer();

public:
	int Get_ClientNum() { return m_iClientNum; };
	void Set_ClientNum(int _ClientNum) { m_iClientNum = _ClientNum; };
	bool Get_PlayerReady() { return m_bClientReady; };
	void Set_PlayerReady(bool _bClientReady) { m_bClientReady = _bClientReady; };
	int Get_Hp() { return m_iHp; };
	void Set_Hp(int _iHp) { m_iHp = _iHp; };
	int Get_Coin() { return m_iCoin; };
	void Set_Coin(int _iCoin) { m_iCoin = _iCoin; };
	int Get_Score() { return m_iScore; };
	void Set_Score(int _iScore) { m_iScore = _iScore; };
	int Get_Posx() { return m_iPosx; };
	void Set_Posx(int _iPosx) { m_iPosx = _iPosx; };
	int Get_Posy() { return m_iPosy; };
	void Set_Posy(int _iPosy) { m_iPosy = _iPosy; };

	void Set_PlayerData() {
		m_iHp = m_splayerdata.hp;
		m_iCoin = m_splayerdata.coin;
		m_iScore = m_splayerdata.score;
		m_iPosx = m_splayerdata.posx;
		m_iPosy = m_splayerdata.posy;
	}

private:	
	int m_iClientNum = 0;
	bool m_bClientReady = false;
	int m_iHp;
	int m_iCoin;
	int m_iScore;
	int m_iPosx;
	int m_iPosy;
};