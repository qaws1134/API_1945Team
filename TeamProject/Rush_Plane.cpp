#include "stdafx.h"
#include "Rush_Plane.h"
#include "ObjMgr.h"
#include "M_Normal.h"
CRush_Plane::CRush_Plane() :m_bBulletOn(false), m_fTurnAngle(0)
{
}


CRush_Plane::~CRush_Plane()
{
	Release();
}


void CRush_Plane::Initialize()
{
	m_iHp = 5;
	//추가한 코드(위)

	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_iExitLate = 1000;
	m_iAttLate = 100;

	m_tInfo.vSize = { 100.f,100.f,0.f };
	m_tInfo.vPos = { 200.f,200.f,0.f };
	m_vP[0] = { -m_tInfo.vSize.x * 0.2f,  -m_tInfo.vSize.y * 0.2f , 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.2f,  -m_tInfo.vSize.y * 0.2f , 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.03f, m_tInfo.vSize.y * 0.2f , 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.03f,m_tInfo.vSize.y * 0.2f , 0.f };

	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_eDir = UP_LEFT;
	m_fSpeed = 5.f;
}

void CRush_Plane::Ai_Pattern()
{

	//턴타임
	if (m_dwExitTime + m_iExitLate < GetTickCount())
	{
		m_bWalk_Out = true;
	}
	//이동
	Dir_Plane(m_bWalk_Out);
	WriteMatrix(m_fAngle);

	if (m_dwAttTime + m_iAttLate < GetTickCount())
	{
		if (!m_bBulletOn)
		{
			CObjMgr::Get_Instance()->Add_Object(CreateBullet<CM_Normal>(), OBJID::BULLET);
			m_bBulletOn = true;
		}
	}
	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);

}

void CRush_Plane::WriteMatrix(float _fRotAngle)
{
	D3DXMATRIX matRotY,matRotZ, matTransl, matParents;
	D3DXMatrixTranslation(&matParents, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	if (!m_bWalk_Out)
	{
		matWorld =matParents;
	}
	else 
	{
		switch (m_eDir)
		{
		case CRush_Plane::DOWN_LEFT:			
			m_fAngle += 4.f;
			if(m_fTurnAngle<45.f)
				m_fTurnAngle += 2.f;
			D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
			D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fTurnAngle));
			break;
		case CRush_Plane::DOWN_RIGHT:
			m_fAngle += 4.f;			
			if (m_fTurnAngle<45.f)
				m_fTurnAngle += 2.f;
			D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
			D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-m_fTurnAngle));	
			break;
		case CRush_Plane::UP_LEFT:
			if (m_fAngle < 180.f)
				m_fAngle += 4.f;
			D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
			D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
			break;
		case CRush_Plane::UP_RIGHT:
			if (m_fAngle < 180.f)
				m_fAngle += 4.f;
			D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-m_fAngle));
			D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
			break;
		}
		matWorld = matRotY*matRotZ*matParents;

	}

}


void CRush_Plane::Dir_Plane(bool _bWalk_Out)
{
	//스폰 시
	//턴 하기 전 
	if (!_bWalk_Out)
		m_tInfo.vDir = { 0.f,1.f,0.f };
	else
	{
		switch (m_eDir)
		{
		case DOWN_LEFT:
			m_tInfo.vDir = { -1.f,1.f,0.f };
			break;
		case DOWN_RIGHT:
			//오른쪽 아래
			m_tInfo.vDir = { 1.f,1.f,0.f };
			break;
		case UP_LEFT:
			if (m_fTurnAngle<90.f)
				m_fTurnAngle += 2.f;
			m_tInfo.vDir.x += -cosf(D3DXToRadian(m_fTurnAngle));
			m_tInfo.vDir.y -= sinf(D3DXToRadian(m_fTurnAngle));
			break;
		case UP_RIGHT:
			if(m_fTurnAngle<90.f)
				m_fTurnAngle += 2.f;
			m_tInfo.vDir.x += cosf(D3DXToRadian(m_fTurnAngle));
			m_tInfo.vDir.y -= sinf(D3DXToRadian(m_fTurnAngle));
			break;
		}
	}
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	m_tInfo.vPos += m_tInfo.vDir*m_fSpeed;
}
