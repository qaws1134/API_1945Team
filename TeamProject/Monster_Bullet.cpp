#include "stdafx.h"
#include "Monster_Bullet.h"
#include "ObjMgr.h"

CMonster_Bullet::CMonster_Bullet(): m_fRotAngle(0), m_iMaxIdx(0), m_iBulletType(0)
{
	ZeroMemory(&m_vPBullet, sizeof(m_vPBullet));
	ZeroMemory(&m_vQBullet, sizeof(m_vQBullet));

}


CMonster_Bullet::~CMonster_Bullet()
{
	Release();

}


int CMonster_Bullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	WriteMatrix();

	if (m_fAngle != 0&& m_iBulletType != 2)
	{
		m_tInfo.vDir.x = cosf(D3DXToRadian(m_fAngle));
		m_tInfo.vDir.y = -sinf(D3DXToRadian(m_fAngle));
	}
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	m_tInfo.vPos += m_tInfo.vDir*m_fSpeed;

	for (int i = 0; i < m_iMaxIdx; ++i)
	{
		D3DXVec3TransformCoord(&m_vQBullet[i], &m_vPBullet[i], &matWorld);
	}
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster_Bullet::Late_Update()
{
	if (m_tInfo.vPos.x < WINCXZERO  || m_tInfo.vPos.x >WINCX
		|| m_tInfo.vPos.y < 0 || m_tInfo.vPos.y > WINCY)
		m_bDead = true;
}

void CMonster_Bullet::Render(HDC _DC)
{
	MoveToEx(_DC, (int)m_vQBullet[0].x, (int)m_vQBullet[0].y, nullptr);
	for (int i = 1; i < m_iMaxIdx; i++)
 		LineTo(_DC, (int)m_vQBullet[i].x, (int)m_vQBullet[i].y);
	LineTo(_DC, (int)m_vQBullet[0].x, (int)m_vQBullet[0].y);
}

void CMonster_Bullet::Release()
{
}
