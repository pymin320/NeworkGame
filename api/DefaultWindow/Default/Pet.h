#pragma once
#include "Obj.h"
class CPet :
	public CObj
{
public:
	CPet();
	~CPet();

public:
	virtual void Initialize(void) override;
	virtual const int&&	 Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Late_Update(void) override;

	void Set_Info(INFO _PlayerInfo) { m_tInfo = _PlayerInfo; }
	RECT Get_MagnetRect() { return m_tMagnetRect; };

	void Magnet();

	bool ReturnMagnet() { return m_bMagnet; };

private:
	int		m_iCount;
	RECT	m_tMagnetRect;
	bool	m_bMagnet;

	int		m_iMagnetCount;

	int		m_iDistance;
};

