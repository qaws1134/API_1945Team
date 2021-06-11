#include "stdafx.h"
#include "BreakBullet.h"
#include "M_Normal.h"
#include "ObjMgr.h"
CBreakBullet::CBreakBullet():m_dwExitTime(GetTickCount()),m_iExitTime(0)
{
}


CBreakBullet::~CBreakBullet()
{
	int ioffsetX = -20;
	int ioffsetY = -20;
	//Up
	for (int i = 0; i < 2; i++)
	{
		CObj* pObj = CAbstractFactory<CM_Normal>::Create(m_tInfo.vPos.x + ioffsetX,m_tInfo.vPos.y, D3DXVECTOR3{ 0.f,-1.f,0.f });
		static_cast<CM_Normal*>(pObj)->Set_BulletType(3);
		CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::M_BULLET);
		ioffsetX += 40;
	}
	CObj* pObj_Up = CAbstractFactory<CM_Normal>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y+ ioffsetY, D3DXVECTOR3{ 0.f,-1.f,0.f });
	static_cast<CM_Normal*>(pObj_Up)->Set_BulletType(3);
	CObjMgr::Get_Instance()->Add_Object(pObj_Up, OBJID::M_BULLET);
	ioffsetX = -20;
	ioffsetY = -20;

	//Down
	for (int i = 0; i < 2; i++)
	{
		CObj* pObj = CAbstractFactory<CM_Normal>::Create(m_tInfo.vPos.x + ioffsetX, m_tInfo.vPos.y, D3DXVECTOR3{0.f,1.f,0.f});
		static_cast<CM_Normal*>(pObj)->Set_BulletType(3);
		CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::M_BULLET);
		ioffsetX += 40;
	}
	CObj* pObj_Down = CAbstractFactory<CM_Normal>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y - ioffsetY, D3DXVECTOR3{ 0.f,1.f,0.f });
	static_cast<CM_Normal*>(pObj_Down)->Set_BulletType(3);
	CObjMgr::Get_Instance()->Add_Object(pObj_Down, OBJID::M_BULLET);


	ioffsetX = -20;
	ioffsetY = -20;
	for (int i = 0; i < 2; i++)
	{
		CObj* pObj = CAbstractFactory<CM_Normal>::Create(m_tInfo.vPos.x , m_tInfo.vPos.y+ioffsetY, D3DXVECTOR3{ -1.f,0.f,0.f });
		static_cast<CM_Normal*>(pObj)->Set_BulletType(3);
		CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::M_BULLET);
		ioffsetY += 40;
	}
	CObj* pObj_Left = CAbstractFactory<CM_Normal>::Create(m_tInfo.vPos.x+ioffsetX, m_tInfo.vPos.y , D3DXVECTOR3{ -1.f,0.f,0.f });
	static_cast<CM_Normal*>(pObj_Left)->Set_BulletType(3);
	CObjMgr::Get_Instance()->Add_Object(pObj_Left, OBJID::M_BULLET);

	ioffsetX = -20;
	ioffsetY = -20;
	for (int i = 0; i < 2; i++)
	{
		CObj* pObj = CAbstractFactory<CM_Normal>::Create(m_tInfo.vPos.x , m_tInfo.vPos.y+ ioffsetY, D3DXVECTOR3{ 1.f,0.f,0.f });
		static_cast<CM_Normal*>(pObj)->Set_BulletType(3);
		CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::M_BULLET);
		ioffsetY += 40;
	}
	CObj* pObj_Right = CAbstractFactory<CM_Normal>::Create(m_tInfo.vPos.x - ioffsetX, m_tInfo.vPos.y , D3DXVECTOR3{ 1.f,0.f,0.f });
	static_cast<CM_Normal*>(pObj_Right)->Set_BulletType(3);
	CObjMgr::Get_Instance()->Add_Object(pObj_Right, OBJID::M_BULLET);


}

void CBreakBullet::Initialize()
{

	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_tInfo.vSize = { 100.f,100.f,0.f };
	m_fSpeed = 6.f;

	m_iExitTime = 1500;
}


void CBreakBullet::WriteMatrix()
{
	m_fSpeed -= 0.05f;
	if (m_dwExitTime + m_iExitTime < GetTickCount())
		m_bDead = true;

	D3DXMATRIX matRot, matRotParent, matTransl, matParents;
	D3DXMatrixTranslation(&matParents, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	matWorld = matParents;
}

void CBreakBullet::Render(HDC _DC)
{
	Ellipse(_DC, m_tInfo.vPos.x-m_tInfo.vSize.x*0.5f
		, m_tInfo.vPos.y - m_tInfo.vSize.y*0.5f
		, m_tInfo.vPos.x + m_tInfo.vSize.x*0.5f
		, m_tInfo.vPos.y + m_tInfo.vSize.y*0.5f);
}

