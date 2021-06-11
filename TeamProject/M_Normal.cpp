#include "stdafx.h"
#include "M_Normal.h"


CM_Normal::CM_Normal()
{
}


CM_Normal::~CM_Normal()
{
	Release();
}

void CM_Normal::Initialize()
{
	if (m_iBulletType == 0 )
	{
		//작은 총알
		m_tInfo.vSize = { 17.f,17.f,0.f };

		m_vPBullet[0] = { m_tInfo.vSize.x*0.4f ,0.f,0.f };

		m_vPBullet[1] = { m_tInfo.vSize.x*0.3f, -m_tInfo.vSize.y*0.2f,0.f };
		m_vPBullet[2] = { m_tInfo.vSize.x*0.1f, -m_tInfo.vSize.y*0.3f,0.f };
		m_vPBullet[3] = { -m_tInfo.vSize.x*0.1f,-m_tInfo.vSize.y*0.3f,0.f };
		m_vPBullet[4] = { -m_tInfo.vSize.x*0.3f,-m_tInfo.vSize.y*0.2f,0.f };
		m_vPBullet[5] = { -m_tInfo.vSize.x*0.4f, 0.f,0.f };
		m_vPBullet[6] = { -m_tInfo.vSize.x*0.3f, m_tInfo.vSize.y*0.2f,0.f };
		m_vPBullet[7] = { -m_tInfo.vSize.x*0.1f, m_tInfo.vSize.y*0.3f,0.f };
		m_vPBullet[8] = { m_tInfo.vSize.x*0.1f, m_tInfo.vSize.y*0.3f,0.f };
		m_vPBullet[9] = { m_tInfo.vSize.x*0.3f, m_tInfo.vSize.y*0.2f,0.f };
		m_iMaxIdx = 10;
		m_fSpeed = 3.3f;
	}
	else if(m_iBulletType == 1)
	{
		//중간크기 총알
		m_tInfo.vSize = { 30.f,30.f,0.f };
		m_vPBullet[0] = { m_tInfo.vSize.x*0.4f ,0.f,0.f };

		m_vPBullet[1] = { m_tInfo.vSize.x*0.3f, -m_tInfo.vSize.y*0.3f,0.f };
		m_vPBullet[2] = { m_tInfo.vSize.x*0.1f, -m_tInfo.vSize.y*0.4f,0.f };
		m_vPBullet[3] = { -m_tInfo.vSize.x*0.1f,-m_tInfo.vSize.y*0.4f,0.f };
		m_vPBullet[4] = { -m_tInfo.vSize.x*0.3f,-m_tInfo.vSize.y*0.3f,0.f };

		m_vPBullet[5] = { -m_tInfo.vSize.x*0.4f, 0.f,0.f };

		m_vPBullet[6] = { -m_tInfo.vSize.x*0.3f, m_tInfo.vSize.y*0.3f,0.f };
		m_vPBullet[7] = { -m_tInfo.vSize.x*0.1f, m_tInfo.vSize.y*0.4f,0.f };
		m_vPBullet[8] = { m_tInfo.vSize.x*0.1f, m_tInfo.vSize.y*0.4f,0.f };
		m_vPBullet[9] = { m_tInfo.vSize.x*0.3f, m_tInfo.vSize.y*0.3f,0.f };
		m_iMaxIdx = 10;
		m_fSpeed = 5.f;
	}
	else if (m_iBulletType == 2)
	{
		m_tInfo.vSize = { 20.f,40.f,0.f };
		m_vPBullet[0] = { -m_tInfo.vSize.x*0.5f , -m_tInfo.vSize.y*0.5f,0.f };
		m_vPBullet[1] = {  m_tInfo.vSize.x*0.5f, -m_tInfo.vSize.y*0.5f,0.f };
		m_vPBullet[2] = {  m_tInfo.vSize.x*0.5f, m_tInfo.vSize.y*0.5f,0.f };
		m_vPBullet[3] = { -m_tInfo.vSize.x*0.5f, m_tInfo.vSize.y*0.5f,0.f };
		m_iMaxIdx = 4;
		m_fSpeed = 6.f;
		//네모총알

	}
	else if (m_iBulletType == 3)
	{
		//break bullet 중간 동그라미
		m_tInfo.vSize = { 200.f,200.f,0.f };
		m_vPBullet[0] = { -m_tInfo.vSize.x*0.8f , -m_tInfo.vSize.y*0.8f,0.f };
		m_vPBullet[1] = { m_tInfo.vSize.x*0.8f, -m_tInfo.vSize.y*0.8f,0.f };
		m_fSpeed = 3.f;
		m_iMaxIdx = 2;
	}
	else if (m_iBulletType == 4)
	{
		//breake bullet 큰 동그라미
		m_tInfo.vSize = { 100.f,100.f,0.f };
		m_vPBullet[0] = { -m_tInfo.vSize.x*0.5f , -m_tInfo.vSize.y*0.5f,0.f };
		m_vPBullet[1] = { m_tInfo.vSize.x*0.5f, -m_tInfo.vSize.y*0.5f,0.f };
		m_fSpeed = 6.f;
		m_iMaxIdx = 2;
	}

	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

}

void CM_Normal::WriteMatrix()
{
	D3DXMATRIX matRot, matRotX,matTrans, matParents;
	D3DXMatrixTranslation(&matParents, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	switch (m_iBulletType)
	{
	case 0:
	case 1:
		m_fRotAngle += 5.f;
		D3DXMatrixRotationZ(&matRot, D3DXToRadian(m_fRotAngle));
		matWorld = matRot*matParents;

		break;
	case 2:
		D3DXMatrixRotationZ(&matRot, D3DXToRadian(-m_fAngle+90));
		matWorld = matRot*matParents;
		break;
	case 3:
	case 4:
		matWorld = matParents;
		break;
	default:
		break;
	}
}
