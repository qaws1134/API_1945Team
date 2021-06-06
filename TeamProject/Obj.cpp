#include "stdafx.h"
#include "Obj.h"


CObj::CObj() : m_fSpeed(0.f), m_bDead(false), m_fAngle(0.f), m_eRenderID(RENDERID::END)
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


