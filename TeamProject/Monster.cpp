#include "stdafx.h"
#include "Monster.h"
#include "ObjMgr.h"

CMonster::CMonster() 
	: m_bWalk_Out(false), m_bItemDrop(false)
	,m_dwExitTime(GetTickCount()),m_iExitLate(0)
	,m_dwAttTime(GetTickCount()),m_iAttLate(0)
	,m_eDir(M_ANGLE::END),m_eExitDir(M_ANGLE::END)
	, m_fTurnAngle(0.f)
{
	ZeroMemory(&m_vDir_Bullet, sizeof(m_vDir_Bullet));
}


CMonster::~CMonster()
{
}





int CMonster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Set_Target();
	Update_Rect();

	Ai_Pattern();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	if (m_bWalk_Out)
	{
		if (m_tInfo.vPos.x+ m_tInfo.vSize.x*0.5f  < WINCXZERO || m_tInfo.vPos.x- m_tInfo.vSize.x*0.5f  > WINCX
			|| m_tInfo.vPos.y+ m_tInfo.vSize.y*0.5f  < 0 || m_tInfo.vPos.y-m_tInfo.vSize.y*0.5f > WINCY)
			m_bDead = true;
	}
	if (m_iHp < 0)
		m_bDead = true;
}



void CMonster::Render(HDC _DC)
{
	MoveToEx(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y, nullptr);
	for (int i = 1; i < 4; i++)
		LineTo(_DC, (int)m_vQ[i].x, (int)m_vQ[i].y);
	LineTo(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y);

}

void CMonster::Set_Target()
{
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();

	if (m_pPlayer)
	{
		m_vDir_Bullet = m_pPlayer->Get_Info().vPos - m_tInfo.vPos;
		D3DXVec3Normalize(&m_vDir_Bullet, &m_vDir_Bullet);
	}
}

void CMonster::Dir_Plane(bool _bWalk_Out)
{

	switch (m_eDir)
	{
	case M_ANGLE::IDLE:
		m_tInfo.vDir = { 0.f,0.f,0.f };
		break;
	case M_ANGLE::LEFT:
		m_tInfo.vDir = { -1.f,0.f,0.f };
		break;
	case M_ANGLE::RIGHT:
		m_tInfo.vDir = { 1.f,0.f,0.f };
		break;
	case M_ANGLE::UP:
		m_tInfo.vDir = { 0.f,-1.f,0.f };
		break;
	case M_ANGLE::DOWN:
		m_tInfo.vDir = { 0.f,1.f,0.f };
		break;
	case M_ANGLE::DOWN_LEFT:
		m_tInfo.vDir = { -1.f,1.f,0.f };
		break;
	case M_ANGLE::DOWN_RIGHT:
		m_tInfo.vDir = { 1.f,1.f,0.f };
		break;
	case M_ANGLE::UP_LEFT:
		if (m_fTurnAngle<90.f)
			m_fTurnAngle += 2.f;
		m_tInfo.vDir.x += -cosf(D3DXToRadian(m_fTurnAngle));
		m_tInfo.vDir.y -= sinf(D3DXToRadian(m_fTurnAngle));
		break;
	case M_ANGLE::UP_RIGHT:
		if (m_fTurnAngle<90.f)
			m_fTurnAngle += 2.f;
		m_tInfo.vDir.x += cosf(D3DXToRadian(m_fTurnAngle));
		m_tInfo.vDir.y -= sinf(D3DXToRadian(m_fTurnAngle));
		break;

	}
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	m_tInfo.vPos += m_tInfo.vDir*m_fSpeed;

}