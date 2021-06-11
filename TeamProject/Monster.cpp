#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster() 
	: m_bWalk_Out(false), m_bItemDrop(false)
	,m_dwExitTime(GetTickCount()),m_iExitLate(0),m_dwAttTime(GetTickCount()),m_iAttLate(0)
{
	ZeroMemory(&m_vDir_Bullet, sizeof(m_vDir_Bullet));
}


CMonster::~CMonster()
{
	Release();
}


int CMonster::Update()
{

	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	Set_Target(m_pPlayer);
	Ai_Pattern();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
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

void CMonster::Release()
{
}

void CMonster::Set_Target(CObj * _pPlayer)
{
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	if (_pPlayer)
	{
		m_vDir_Bullet = _pPlayer->Get_Info().vPos - m_tInfo.vPos;
		D3DXVec3Normalize(&m_vDir_Bullet, &m_vDir_Bullet);
	}
}
