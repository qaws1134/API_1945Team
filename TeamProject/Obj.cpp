#include "stdafx.h"
#include "Obj.h"


CObj::CObj() : m_fSpeed(0.f), m_bDead(false), m_fAngle(0.f), m_eRenderID(RENDERID::END), m_iHp(0)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
	ZeroMemory(&m_vP, sizeof(m_vP));
	ZeroMemory(&m_vQ, sizeof(m_vQ));
	D3DXMatrixIdentity(&matWorld);
}


CObj::~CObj()
{
}

void CObj::Update_Rect()
{

	m_tRect.left = m_tInfo.vPos.x - m_tInfo.vSize.x * 0.2f;
	m_tRect.right = m_tInfo.vPos.x + m_tInfo.vSize.x * 0.2f;
	m_tRect.top = m_tInfo.vPos.y - m_tInfo.vSize.y * 0.2f;
	m_tRect.bottom = m_tInfo.vPos.y + m_tInfo.vSize.y * 0.2f;
}

void CObj::Set_Hp()
{
	m_iHp -= 1;
}

int CObj::Get_Hp()
{
	return m_iHp;
}
