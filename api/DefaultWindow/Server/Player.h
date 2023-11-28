#pragma once

class CPlayer
{
private:
	struct m_sPlayerData {
		int hp, coin, score;
	};
public:
	m_sPlayerData m_splayerdata;

public:
	CPlayer();
	virtual ~CPlayer();

public:
	bool Get_PlayerReady() { return m_bClientReady; };
	void Set_PlayerReady(bool _bClientReady) { m_bClientReady = _bClientReady; };
	int Get_Hp() { return m_iHp; };
	void Set_Hp(int _iHp) { m_iHp = _iHp; };
	int Get_Coin() { return m_iCoin; };
	void Set_Coin(int _iCoin) { m_iCoin = _iCoin; };
	int Get_Score() { return m_iScore; };
	void Set_Score(int _iScore) { m_iScore = _iScore; };

	void Set_PlayerData() {
		m_iHp = m_splayerdata.hp;
		m_iCoin = m_splayerdata.coin;
		m_iScore = m_splayerdata.score;
	}

private:	
	int m_iClientNum = 0;
	bool m_bClientReady = false;
	int m_iHp;
	int m_iCoin;
	int m_iScore;
};