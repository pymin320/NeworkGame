#include "stdafx.h"
#include "TileMgr.h"
#include "CAbstractFactory.h"

CTileMgr*	CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	/*for (int i = 0; i < 25; ++i)
	{
		float	fX = float(124 * i);
		float	fY = 550;

		CObj*	pTile = CAbstractFactory<CTile>::Create(fX, fY);
		m_vecTile.push_back(pTile);
	}
	for (int i = 27; i < 65; ++i)
	{
		float	fX = float(124 * i);
		float	fY = 550;

		CObj*	pTile = CAbstractFactory<CTile>::Create(fX, fY);
		m_vecTile.push_back(pTile);
	}

	for (int i = 68; i < 200; ++i)
	{
		float	fX = float(124 * i);
		float	fY = 550;

		CObj*	pTile = CAbstractFactory<CTile>::Create(fX, fY);
		m_vecTile.push_back(pTile);
	}*/


}

void CTileMgr::Update()
{
	for (auto& iter : m_vecTile)
		iter->Update();
}

void CTileMgr::Late_Update()
{
	for (auto& iter : m_vecTile)
		iter->Late_Update();
}


void CTileMgr::Render(HDC hDC)
{
	for (auto& iter : m_vecTile)
		iter->Render(hDC);
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
}
