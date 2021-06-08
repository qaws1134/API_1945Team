#include "stdafx.h"
#include "SuperFly.h"
#include "Super_Bullet.h"
#include "ObjMgr.h"

CSuperFly::CSuperFly()
{
	ZeroMemory(&m_Fly, sizeof(m_Fly));
}

CSuperFly::~CSuperFly()
{
	Release();
}

void CSuperFly::Initialize()
{
	m_delay = 120;
	m_Time = GetTickCount();
	m_eRenderID = RENDERID::OBJECT;

	D3DXMatrixIdentity(&matWorld);

	m_tInfo.vSize = { 50.0f, 70.0f, 0.0f };
	m_tInfo.vDir = { 0.0f, 0.0f, 0.0f };

	m_vP[0] = { -m_tInfo.vSize.x * 0.3f, -m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[1] = { m_tInfo.vSize.x  * 0.3f, -m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[2] = { m_tInfo.vSize.x  * 0.5f, m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f , 0.f };

	m_fSpeed = 10.f;

	m_Fly.vPos = { m_tInfo.vPos.x, m_tInfo.vPos.y + 10.f, 0.0f };
	m_Fly.vSize = { 250.0f, 50.0f, 0.0f };
}

int CSuperFly::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	D3DXMATRIX matParentScale, matParentTrans, matParentWorld;
	D3DXMatrixTranslation(&matParentTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	D3DXMATRIX matScale, matRotZ, matRotX, matRotY, matTrans, matRelRotZ, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans, 0.0f, 0.0f, 0.f);
	D3DXMatrixRotationZ(&matRelRotZ, D3DXToRadian(m_fAngle));

	matWorld = matScale * matTrans * matParentTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
	}
	m_tInfo.vPos.y -= m_fSpeed;
	m_Fly.vPos.y -= m_fSpeed;
	if (m_Time + m_delay < GetTickCount())
	{
		Basic_Attack();
		Target_Attack();
		m_Time = GetTickCount();
	}
	Update_Rect();
	Correct_Rect();
	return OBJ_NOEVENT;
}

void CSuperFly::Late_Update()
{
	if (m_tInfo.vPos.x < 0 || m_tInfo.vPos.x > WINCX
		|| m_tInfo.vPos.y < 0 || m_tInfo.vPos.y > WINCY)
		m_bDead = true;
}

void CSuperFly::Render(HDC _DC)
{
	MoveToEx(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y, nullptr);
	for (int i = 1; i < 4; ++i)
		LineTo(_DC, (int)m_vQ[i].x, (int)m_vQ[i].y);
	LineTo(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y);
	Rectangle(_DC, (int)(m_Fly.vPos.x - m_Fly.vSize.x * 0.5), (int)(m_Fly.vPos.y - m_Fly.vSize.y * 0.5), (int)(m_Fly.vPos.x + m_Fly.vSize.x * 0.5), (int)(m_Fly.vPos.y + m_Fly.vSize.y * 0.5));
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CSuperFly::Release()
{
}

void CSuperFly::Basic_Attack()
{
	for (int i = -100.f; i <= 140; i += 55)
	{
		CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Basic_Bullet>(m_tInfo.vPos.x + i, m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f, 0.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Basic_Bullet>(m_tInfo.vPos.x + i - 20.f, m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f, 145.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
	}
}

void CSuperFly::Target_Attack()
{
	for(int i = -120.f; i <= 120.f; i += 60.f)
		CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Super_Bullet>(m_tInfo.vPos.x + i, m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f + 10.f, 0.0f, 5.f, 5.f, Basic_Bullet::BULLET_STATE::TARGET), OBJID::BULLET);

}

void CSuperFly::Correct_Rect()
{
	m_tRect.left -= m_tInfo.vSize.x * 2.3f;
	m_tRect.right += m_tInfo.vSize.x * 2.3f;

	m_tRect.bottom += m_tInfo.vSize.y * 0.4f;
}
