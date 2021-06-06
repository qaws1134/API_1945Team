#include "stdafx.h"
#include "SuperFly.h"
#include "ObjMgr.h"

CSuperFly::CSuperFly()
{
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

	m_tInfo.vPos = { 200.0f, 200.0f, 0.0f };
	m_tInfo.vSize = { 300.0f, 150.0f, 0.0f };
	m_tInfo.vDir = { 0.0f, 0.0f, 0.0f };

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[1] = { m_tInfo.vSize.x  * 0.5f, -m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[2] = { m_tInfo.vSize.x  * 0.8f, m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.8f, m_tInfo.vSize.y * 0.5f , 0.f };

	m_fSpeed = 10.f;
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
	// 행렬의 곱셈의 순서는 그냥 외워. 
	// 스 * 자 *이 * 공 * 부 
	// 케일  전  동	전	 모
	matWorld = matScale * matTrans * matParentTrans;

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
	}
	m_tInfo.vPos.y -= m_fSpeed;
	if (m_Time + m_delay < GetTickCount())
	{
		Basic_Attack();
		m_Time = GetTickCount();
	}
	return OBJ_NOEVENT;
}

void CSuperFly::Late_Update()
{
	if (m_tInfo.vPos.y < 0 || m_tInfo.vPos.x > WINCX
		|| m_tInfo.vPos.y < 0 || m_tInfo.vPos.x > WINCY)
		m_bDead = true;
}

void CSuperFly::Render(HDC _DC)
{
	MoveToEx(_DC, m_vQ[0].x, m_vQ[0].y, nullptr);
	for (int i = 1; i < 4; ++i)
		LineTo(_DC, m_vQ[i].x, m_vQ[i].y);
	LineTo(_DC, m_vQ[0].x, m_vQ[0].y);

}

void CSuperFly::Release()
{
}

void CSuperFly::Basic_Attack()
{

	CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Basic_Bullet>(m_tInfo.vPos.x - 140.f, m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f, 0.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
	CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Basic_Bullet>(m_tInfo.vPos.x - 120.f, m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f, 145.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
	
	CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Basic_Bullet>(m_tInfo.vPos.x - 80.f, m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f, 0.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
	CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Basic_Bullet>(m_tInfo.vPos.x - 60.f, m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f, 145.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

	CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Basic_Bullet>(m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f, 0.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
	CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Basic_Bullet>(m_tInfo.vPos.x , m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f, 145.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);


	CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Basic_Bullet>(m_tInfo.vPos.x , m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f, 0.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
	CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Basic_Bullet>(m_tInfo.vPos.x + 20.f, m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f, 145.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

	CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Basic_Bullet>(m_tInfo.vPos.x + 60.f, m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f, 0.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
	CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Basic_Bullet>(m_tInfo.vPos.x + 80.f, m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f, 145.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

	CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Basic_Bullet>(m_tInfo.vPos.x + 120.f, m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f, 0.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);
	CObjMgr::Get_Instance()->Add_Object(Create_SuperFlyBullet<Basic_Bullet>(m_tInfo.vPos.x + 140, m_tInfo.vPos.y - m_tInfo.vSize.y * 0.7f, 145.0f, 5, 60, Basic_Bullet::BULLET_STATE::BASIC), OBJID::BULLET);

}