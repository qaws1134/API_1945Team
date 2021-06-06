#include "stdafx.h"
#include "Super_Bullet.h"


Super_Bullet::Super_Bullet() :m_eBulletType(BULLET_STATE::END), m_Move(false), m_Still(0)
{
	ZeroMemory(&m_Fly, sizeof(m_Fly));
}


Super_Bullet::~Super_Bullet()
{
}

void Super_Bullet::Initialize()
{

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y , 0.f };
	m_vP[1] = { m_tInfo.vSize.x  * 0.5f, -m_tInfo.vSize.y , 0.f };
	m_vP[2] = { m_tInfo.vSize.x  * 0.7f, m_tInfo.vSize.y , 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.7f, m_tInfo.vSize.y , 0.f };


	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_fSpeed = 25.f;
	m_Still = 80;
}

int Super_Bullet::Update()
{
	D3DXMATRIX matParentScale, matParentTrans, matParentWorld;
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eBulletType == BULLET_STATE::BOMB)
		Bomb_Update();


	return OBJ_NOEVENT;
}

void Super_Bullet::Late_Update()
{
	if (m_tInfo.vPos.y < 0 || m_tInfo.vPos.x > WINCX
		|| m_tInfo.vPos.y < 0 || m_tInfo.vPos.x > WINCY)
		m_bDead = true;
}

void Super_Bullet::Render(HDC _DC)
{
	MoveToEx(_DC, m_vQ[0].x, m_vQ[0].y, nullptr);
	for (int i = 1; i < 4; ++i)
		LineTo(_DC, m_vQ[i].x, m_vQ[i].y);
	LineTo(_DC, m_vQ[0].x, m_vQ[0].y);
}

void Super_Bullet::Release()
{
}

void Super_Bullet::Bomb_Update()
{
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
	if (m_tInfo.vPos.y < 450)
	{
		m_fSpeed = 2.5f;
	}

	if(m_Move)
		m_tInfo.vPos.y -= m_fSpeed;
}



void Super_Bullet::Set_Size(float _xSize, float _ySize)
{
	m_tInfo.vSize.x = _xSize;
	m_tInfo.vSize.y = _ySize;
}

void Super_Bullet::Set_BulletType(BULLET_STATE _BULLET)
{
	m_eBulletType = _BULLET;
}
