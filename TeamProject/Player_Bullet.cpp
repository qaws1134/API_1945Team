#include "stdafx.h"
#include "Player_Bullet.h"


Player_Bullet::Player_Bullet()
{
}


Player_Bullet::~Player_Bullet()
{
}

void Player_Bullet::Initialize()
{
	m_tInfo.iCX = 10;
	m_tInfo.iCY = 15;
	m_vP[0] = { -m_tInfo.iCX * 0.5f, -m_tInfo.iCY * 0.5f , 0.f };
	m_vP[1] = { m_tInfo.iCX  * 0.5f, -m_tInfo.iCY * 0.5f , 0.f };
	m_vP[2] = { m_tInfo.iCX  * 0.5f, m_tInfo.iCY * 0.5f , 0.f };
	m_vP[3] = { -m_tInfo.iCX  * 0.5f, m_tInfo.iCY * 0.5f , 0.f };


	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_fSpeed = 5.f;
}

int Player_Bullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	//D3DXMatrixScaling(&matScale, 2.f, 2.f, 1.f);
	//D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-m_fAngle));
	//D3DXMatrixRotationX(&matRotX, D3DXToRadian(m_fAngle));
	//D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.f);
	//D3DXMatrixRotationZ(&matRelRotZ, D3DXToRadian(m_fAngle));

	D3DXMATRIX matScale, matRotY, matRotX, matTrans, matRelRotZ, matWorld;
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(145.0f));
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(45.0f));
	D3DXMatrixTranslation(&matTrans, m_tInfo.fX, m_tInfo.fY, 0.f);
	// 행렬의 곱셈의 순서는 그냥 외워. 
	// 스 * 자 *이 * 공 * 부 
	// 케일  전  동	전	 모


	matWorld = matScale * matRotX * matRotY * matTrans;
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);

		//m_vP[i].y -= 1;
	}
	m_tInfo.fY -= m_fSpeed;

	Update_Rect();
	return OBJ_NOEVENT;
}

void Player_Bullet::Late_Update()
{
	if (m_tInfo.fX < 0 || m_tInfo.fX > WINCX
		|| m_tInfo.fY < 0 || m_tInfo.fY > WINCY)
		m_bDead = true;
}

void Player_Bullet::Render(HDC _DC)
{
	MoveToEx(_DC, m_vQ[0].x, m_vQ[0].y, nullptr);
	for (int i = 1; i < 4; ++i)
		LineTo(_DC, m_vQ[i].x, m_vQ[i].y);
	LineTo(_DC, m_vQ[0].x, m_vQ[0].y);
}

void Player_Bullet::Release()
{
}


