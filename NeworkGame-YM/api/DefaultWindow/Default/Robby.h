#pragma once
#include "Scene.h"
class CRobby :
	public CScene
{
public:
	CRobby();
	~CRobby();
public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	POINT			m_tMouse;
	INFO			m_tMouseInfo;
	RECT			m_tMouseRect;

	RECT			m_tButton;
	RECT			m_tStartButton;

	RECT			m_tHP;
	float			m_iHp;
	int				m_iHpCount;

	bool			m_bReady;
	int				m_iCookieType;

	bool			m_bBuyZombie;
	bool			m_bBuyDevil;

	RECT			m_tPurchaseDevil;
	RECT			m_tPurchaseZombie;

	RECT			m_tCrickDevil;
	RECT			m_tCrickZombie;

	RECT			m_tPurchaseNormal;
	RECT			m_tPurchaseRare;


	int		m_iCoinFrame;
	int		m_iCount;

	FRAME	m_tFrame;

	RECT	m_tRect;

	int		m_iCoin;
	int		m_iCoin2;

	INFO	m_tScore;
	RECT	m_tScoreRect;
	int		m_iScore;

	bool	m_bNormal;
	bool	m_bRare;

	int		m_iJellyType;
};

