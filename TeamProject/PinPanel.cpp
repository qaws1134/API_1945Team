#include "stdafx.h"
#include "PinPanel.h"
#include "M_Normal.h"

CPinPanel::CPinPanel()
{
}


CPinPanel::~CPinPanel()
{
}

void CPinPanel::Initialize()
{
	m_iHp = 10;

	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_iAttLate = 1500;
	m_iExitLate = 4000;

	m_tInfo.vSize = { 50.f,50.f,0.f };
	m_tInfo.vPos = { 200.f,200.f,0.f };

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f,  -m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[1] = {  m_tInfo.vSize.x * 0.5f,  -m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[2] = {  m_tInfo.vSize.x * 0.5f,   m_tInfo.vSize.y * 0.5f , 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f,   m_tInfo.vSize.y * 0.5f , 0.f };

	m_fAngle =0.f;
	m_fSpeed = 3.f;
}

void CPinPanel::Release()
{
}

void CPinPanel::Ai_Pattern()
{

	//еое╦юс
	if (m_dwExitTime + m_iExitLate < GetTickCount())
	{
		if (!m_bWalk_Out)
		{
			m_bWalk_Out = true;
			GetTickCount();
		}
	}
	if (!m_bWalk_Out)
	{
		if (m_tInfo.vPos.x < WINCXZERO + 100 || m_tInfo.vPos.x > WINCX - 100)
		{
			m_eDir = M_ANGLE::IDLE;
		}
		else if (m_tInfo.vPos.y < 100 || m_tInfo.vPos.y > WINCY - 100)
		{
			m_eDir = M_ANGLE::IDLE;
		}
	}
	Dir_Plane(m_bWalk_Out);
	WriteMatrix(m_fAngle);

	if (!m_bWalk_Out)
	{
		if (m_dwAttTime + m_iAttLate < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(CreateBullet<CM_Normal>(), OBJID::M_BULLET);
			m_dwAttTime = GetTickCount();
		}
	}

	for (int i = 0; i < 4; i++)
		D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &matWorld);
}

void CPinPanel::WriteMatrix(float _fRotAngle)
{
	D3DXMATRIX matRot, matTransl, matParents;
	D3DXMatrixTranslation(&matParents, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	D3DXMatrixIdentity(&matRot);

	m_fAngle += 5;
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(m_fAngle));
	matWorld = matRot*matParents;
}

void CPinPanel::Late_Update()
{

}
