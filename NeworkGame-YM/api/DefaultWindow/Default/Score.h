#pragma once
#include "Scene.h"
class CScore :
	public CScene
{
public:
	CScore();
	virtual ~CScore();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:
	int		m_iScore;
	int		m_iCoin;

	INFO	m_tCoin;
	RECT	m_tCoinRect;

	INFO	m_tScore;
	RECT	m_tScoreRect;

	int		m_iHighScore;

	bool	m_bHighScore;
};

