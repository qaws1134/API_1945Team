#include "stdafx.h"
#include "Rush_Plane.h"
#include "ObjMgr.h"
#include "M_Normal.h"
CRush_Plane::CRush_Plane() :m_bBulletOn(false), m_bInitDir(false)
{
}


CRush_Plane::~CRush_Plane()
{
	Release();
}


void CRush_Plane::Initialize()
{
	m_iHp = 1;
	//추가한 코드(위)

	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_iExitLate = 1300;
	m_iAttLate = 100;

	m_tInfo.vSize = { 100.f,100.f,0.f };
	m_tInfo.vPos = { 200.f,200.f,0.f };
	m_vP[0] = { -m_tInfo.vSize.x * 0.2f,  -m_tInfo.vSize.y * 0.2f , 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.2f,  -m_tInfo.vSize.y * 0.2f , 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.03f, m_tInfo.vSize.y * 0.2f , 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.03f,m_tInfo.vSize.y * 0.2f , 0.f };
	m_fSpeed = 3.f;
}

void CRush_Plane::Ai_Pattern()
{

	//턴타임
	if (m_dwExitTime + m_iExitLate < GetTickCount())
	{
		Set_eDir(m_eExitDir);
		if (!m_bInitDir)
		{
			m_tInfo.vDir = { 0.f,1.f,0.f };
			m_bInitDir = true;
			m_fAngle = 45;
		}
		m_bWalk_Out = true;
	}
	//이동
	Dir_Plane(m_bWalk_Out);
	WriteMatrix(m_fAngle);

	if (m_dwAttTime + m_iAttLate < GetTickCount())
	{
		if (!m_bBulletOn)
		{
			CObjMgr::Get_Instance()->Add_Object(CreateBullet<CM_Normal>(), OBJID::M_BULLET);
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
	D3DXMatrixIdentity(&matRotZ);
	//if (!m_bWalk_Out)
	//{
	//	matWorld =matParents;
	//}
	//else 
	//{

	switch (m_eDir)
	{
	case M_ANGLE::DOWN_LEFT:
		m_fAngle += 4.f;
		if(m_fTurnAngle<45.f)
			m_fTurnAngle += 2.f;
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fTurnAngle));
		break;
	case M_ANGLE::DOWN_RIGHT:
		m_fAngle += 4.f;			
		if (m_fTurnAngle<45.f)
			m_fTurnAngle += 2.f;
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-m_fTurnAngle));	
		break;
	case M_ANGLE::UP_LEFT:
		if (m_fAngle < 180.f)
			m_fAngle += 4.f;

		D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
		break;
	case M_ANGLE::UP_RIGHT:
		if (m_fAngle < 180.f)
			m_fAngle += 4.f;

		D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
		D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-m_fAngle));
		matWorld = matRotY*matRotZ*matParents;
		break;
	default :
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
	}
	matWorld = matRotY*matRotZ*matParents;

	//}

}



void CRush_Plane::Release()
{
}
