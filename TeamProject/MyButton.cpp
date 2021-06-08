#include "stdafx.h"
#include "MyButton.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
CMyButton::CMyButton()
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize()
{
	m_tInfo.vSize.x = 150.f;
	m_tInfo.vSize.y = 50.f;

	m_tRect = { (LONG)(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5), (LONG)(m_tInfo.vPos.y - m_tInfo.vSize.y * 0.5),(LONG)(m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5), (LONG)(m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5) };
	m_eRenderID = RENDERID::UI;
}

int CMyButton::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	return OBJ_NOEVENT;
}

void CMyButton::Late_Update()
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::STAGE);
			return;
		}
	}
}

void CMyButton::Render(HDC _DC)
{
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMyButton::Release()
{
}
