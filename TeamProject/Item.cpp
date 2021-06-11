#include "stdafx.h"
#include "Item.h"
#include "ObjMgr.h"

CItem::CItem():m_bStart(false), m_fRotAngle(0), m_bReflect(false), m_pPlayer(nullptr)
{
	ZeroMemory(&m_vPItem, sizeof(m_vPItem));
	ZeroMemory(&m_vQItem, sizeof(m_vQItem));
}


CItem::~CItem()
{
	Release();
}



int CItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bStart)
		Dir_Item();
	WriteMatrix();
	Reflect_item();

	m_tInfo.vPos += m_tInfo.vDir*m_fSpeed;


	Update_Rect();
	return OBJ_NOEVENT;
}

void CItem::Late_Update()
{
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	RECT rc = {};
	if (IntersectRect(&rc, &m_pPlayer->Get_Rect(), &m_tRect))
	{
		Use_Item(m_pPlayer);
	}
}

void CItem::Release()
{

}

void CItem::Dir_Item()
{
	float randX = 1.f;
	float randY = 1.f;
	if (rand() % 2 == 1)
		randX *= -1;
	if (rand() % 2 == 1)
		randY *= -1;

	float randPlusX = float(rand() % 10 + 1);
	float randPlusY = float(rand() % 10 + 1);

	randPlusX = 1.f / randPlusX; 
	randPlusY = 1.f / randPlusY;
	randX = randX * randPlusX;
	randY = randY * randPlusY;
	
	m_tInfo.vDir = { randX ,randY,0 };
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	m_bStart = true;
}

void CItem::Reflect_item()
{
	if (m_tInfo.vPos.x < WINCXZERO || m_tInfo.vPos.x > WINCX - 100)
			m_tInfo.vDir.x += 2.0f* -m_tInfo.vDir.x;
	else if (m_tInfo.vPos.y < 100 || m_tInfo.vPos.y > WINCY - 100)
			m_tInfo.vDir.y += 2.0f* -m_tInfo.vDir.y;
}
