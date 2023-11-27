#pragma once

class CPlayer
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	bool Get_PlayerReady() { return m_bClientReady; };
	void Set_PlayerReady(bool _bClientReady) { m_bClientReady = _bClientReady; };

private:
	int m_iClientNum = 0;
	bool m_bClientReady = false;
};