#include "stdafx.h"
#include "UiMgr.h"
#include "CAbstractFactory.h"

CUiMgr* CUiMgr::m_pInstance = nullptr;

CUiMgr::CUiMgr()
{
}


CUiMgr::~CUiMgr()
{
	Release();
}

void CUiMgr::Initialize()
{
	CObj* pUi = CAbstractFactory<CUi>::Create();
	m_listUi.push_back(pUi);
}

void CUiMgr::Update()
{
	for (auto& iter : m_listUi)
		iter->Update();
}

void CUiMgr::Late_Update()
{
	for (auto& iter : m_listUi)
		iter->Late_Update();
}

void CUiMgr::Render(HDC hDC)
{
	for (auto& iter : m_listUi)
		iter->Render(hDC);
}

void CUiMgr::Release()
{
	for_each(m_listUi.begin(), m_listUi.end(), CDeleteObj());
	m_listUi.clear();
}