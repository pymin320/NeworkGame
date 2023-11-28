#pragma once
#include "Include.h"

class CScoreMgr
{
public:
	CScoreMgr();
	~CScoreMgr();

	void Initialize(void);
	int Update(void);
	void Release(void);

	static CScoreMgr*& Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CScoreMgr;
		}

		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			Safe_Delete<CScoreMgr*>(m_pInstance);
			m_pInstance = nullptr;
		}
	}

	static int Get_Score()
	{
		return m_iScore;
	}

	static void Plus_Score(const int& _coin)
	{
		m_iScore += _coin;
	}
	static int Get_Coin()
	{
		return m_iCoin;
	}

	static void Reset_Coin()
	{
		m_iCoin = 0;
	}

	static void Plus_Coin(const int& _coin)
	{
		m_iCoin += _coin;
		m_iMaxCoin += _coin;
	}

	static int& Get_MaxCoin()
	{
		return m_iMaxCoin;
	}

	static void Plus_MaxCoin(const int& _coin)
	{
		m_iMaxCoin += _coin;
	}


	static void Set_Hp(const float& _Hp)
	{
		m_fHp = _Hp * 80 + 150;
	}
	static void Reset_Hp()
	{
		m_fHp = 0;
	}
	static float Get_Hp()
	{
		return m_fHp;
	}

	static int Get_JellyType()
	{
		return m_iJellyType;
	}

	static void Set_JellyType(int _JellyType)
	{
		m_iJellyType = _JellyType;
	}

	static void	Set_CookieType(int _CookieType) 
	{
		m_iCookieType = _CookieType; 
	}

	static int Get_CookieType()
	{
		return m_iCookieType;
	}

	static bool	Set_HighScore(int _Score)
	{
		if (_Score >= m_iHighScore)
		{
			m_iHighScore = _Score;
			return true;
		}
		else
			return false;
	}

	static void Reset_Score()
	{
		m_iScore = 0;
	}

	static int Get_HighScore()
	{
		return m_iHighScore;
	}

private:
	static CScoreMgr* m_pInstance;
	static int m_iScore;
	static int m_iCoin;
	static float m_fHp;
	static int m_iJellyType;
	static int m_iCookieType;
	static int m_iHighScore;
	static int m_iMaxCoin;
};