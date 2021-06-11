#include "stdafx.h"
#include "Basic_Bullet.h"


Basic_Bullet::Basic_Bullet():m_eBulletType(BULLET_STATE::END), m_Move(false), m_Still(0)
{
}


Basic_Bullet::~Basic_Bullet()
{
}

void Basic_Bullet::Initialize()
{
		m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f , 0.f };
		m_vP[1] = { m_tInfo.vSize.x  * 0.5f, -m_tInfo.vSize.y * 0.5f , 0.f };
		m_vP[2] = { m_tInfo.vSize.x  * 0.2f, m_tInfo.vSize.y * 0.5f , 0.f };
		m_vP[3] = { -m_tInfo.vSize.x * 0.2f, m_tInfo.vSize.y * 0.5f , 0.f };
	
		m_tInfo.vDir = { -1.0f, 1.0f, 0.f };
		m_eRenderID = RENDERID::OBJECT;
		D3DXMatrixIdentity(&matWorld);
	
		m_fSpeed = 25.f;
		m_Still = 80;
		m_tInfo.vPos.x -= 8;
		m_tInfo.vPos.y -= 30;
}

int Basic_Bullet::Update()
{
	D3DXMATRIX matParentScale, matParentTrans, matParentWorld;
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eBulletType == BULLET_STATE::BASIC)
		BasicBullet_Update();
	else if (m_eBulletType == BULLET_STATE::CHARGE)
		ChargeBullet_Update();

	Update_Rect();
	Correct_Rect();
	return OBJ_NOEVENT;
}

void Basic_Bullet::Late_Update()
{
	if (m_tInfo.vPos.x < 0 || m_tInfo.vPos.x > WINCX
		|| m_tInfo.vPos.y < 0 || m_tInfo.vPos.y > WINCY)
		m_bDead = true;
}

void Basic_Bullet::Render(HDC _DC)
{
	MoveToEx(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y, nullptr);
	for (int i = 1; i < 4; ++i)
		LineTo(_DC, (int)m_vQ[i].x, (int)m_vQ[i].y);
	LineTo(_DC, (int)m_vQ[0].x, (int)m_vQ[0].y);

}

void Basic_Bullet::Release()
{
}

void Basic_Bullet::BasicBullet_Update()
{
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
}

void Basic_Bullet::ChargeBullet_Update()
{
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
		if(m_Move)
			m_tInfo.vPos.y -= m_fSpeed;
}



void Basic_Bullet::Set_Size(float _xSize, float _ySize)
{
	m_tInfo.vSize.x = _xSize;
	m_tInfo.vSize.y = _ySize;
}

void Basic_Bullet::Set_BulletType(BULLET_STATE _BULLET)
{
	m_eBulletType = _BULLET;
}

void Basic_Bullet::Correct_Rect()
{
	m_tRect.left -= (LONG)(m_tInfo.vSize.x * 0.5f);
	m_tRect.right += (LONG)(m_tInfo.vSize.x * 0.5f);
	m_tRect.bottom += (LONG)(m_tInfo.vSize.y * 0.7f);

	if (m_eBulletType == BULLET_STATE::CHARGE)
	{
		m_tRect.left += (LONG)(m_tInfo.vSize.x * 0.2f);
		m_tRect.right -= (LONG)(m_tInfo.vSize.x * 0.2f);
		m_tRect.top -= (LONG)(m_tInfo.vSize.y * 0.1f);
		m_tRect.bottom -= (LONG)(m_tInfo.vSize.y * 0.18f);
	}
}


