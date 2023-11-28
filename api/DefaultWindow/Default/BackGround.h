#pragma once
#include "Obj.h"
class CBackGround :
	public CObj
{
public:
	CBackGround();
	virtual ~CBackGround();

public:
	virtual void Initialize(void) override;
	virtual const int&&	 Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Late_Update(void) override;

private:
	INFO	m_tBackInfo;
	float	m_fScroll;

	INFO	m_Tile;
	RECT	m_TileRect;
	
	bool	m_bSound;
};

