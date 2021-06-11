#include "stdafx.h"
#include "Boom.h"
#include "Player.h"

CBoom::CBoom()
{
}


CBoom::~CBoom()
{
	Release();
}

void CBoom::Initialize()
{
	//m_tInfo.vPos = { 300.f,300.f,0.f };
	m_tInfo.vSize = { 40.f,40.f,0.f };

	m_vPItem[0] = { -m_tInfo.vSize.x*0.4f ,-m_tInfo.vSize.y*0.5f,0.f };

	m_vPItem[1] = { m_tInfo.vSize.x*0.2f, -m_tInfo.vSize.y*0.5f,0.f };
	m_vPItem[2] = { m_tInfo.vSize.x*0.3f, -m_tInfo.vSize.y*0.4f,0.f };
	m_vPItem[3] = { m_tInfo.vSize.x*0.3f, 0,0.f };
	m_vPItem[4] = { m_tInfo.vSize.x*0.1f, m_tInfo.vSize.y*0.1f,0.f };

	m_vPItem[5] = { -m_tInfo.vSize.x*0.3f, m_tInfo.vSize.y*0.1f,0.f };

	m_vPItem[6] = {  m_tInfo.vSize.x*0.0f, m_tInfo.vSize.y*0.1f,0.f };

	m_vPItem[7] = { m_tInfo.vSize.x*0.3f, m_tInfo.vSize.y*0.2f,0.f };
	m_vPItem[8] = { m_tInfo.vSize.x*0.3f, m_tInfo.vSize.y*0.5f,0.f };
	m_vPItem[9] = {	m_tInfo.vSize.x*0.2f, m_tInfo.vSize.y*0.6f,0.f };
	m_vPItem[10] = { -m_tInfo.vSize.x*0.4f,m_tInfo.vSize.y*0.6f,0.f };


	m_vPItem[11] = { -m_tInfo.vSize.x* 0.3f,  -m_tInfo.vSize.y*0.4f,0.f };
	m_vPItem[12] = {  m_tInfo.vSize.x* 0.1f,  -m_tInfo.vSize.y*0.4f,0.f };
	m_vPItem[13] = {  m_tInfo.vSize.x* 0.2f,  -m_tInfo.vSize.y*0.3f,0.f };
	m_vPItem[14] = {  m_tInfo.vSize.x* 0.2f,  -m_tInfo.vSize.y*0.1f,0.f };
	m_vPItem[15] = {  m_tInfo.vSize.x* 0.1f, 0,0.f };
	m_vPItem[16] = { -m_tInfo.vSize.x* 0.3f, 0,0.f };


	m_vPItem[17] = { -m_tInfo.vSize.x* 0.3f, m_tInfo.vSize.y*0.2f,0.f };
	m_vPItem[18] = { m_tInfo.vSize.x* 0.1f,  m_tInfo.vSize.y*0.2f,0.f };
	m_vPItem[19] = { m_tInfo.vSize.x* 0.2f,  m_tInfo.vSize.y*0.3f,0.f };
	m_vPItem[20] = { m_tInfo.vSize.x* 0.2f,  m_tInfo.vSize.y*0.4f,0.f };
	m_vPItem[21] = { m_tInfo.vSize.x* 0.1f,  m_tInfo.vSize.y*0.5f,0.f };
	m_vPItem[22] = { -m_tInfo.vSize.x* 0.3f, m_tInfo.vSize.y*0.5f,0.f };


	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);

	m_fSpeed = 2.f;
}

void CBoom::Render(HDC _DC)
{
	//Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(_DC, (int)m_vQItem[0].x, (int)m_vQItem[0].y, nullptr);
	for (int i = 1; i < 11; i++)
		LineTo(_DC, (int)m_vQItem[i].x, (int)m_vQItem[i].y);
	LineTo(_DC, (int)m_vQItem[0].x, (int)m_vQItem[0].y);

	MoveToEx(_DC, (int)m_vQItem[11].x, (int)m_vQItem[11].y, nullptr);
	for (int i = 12; i < 17; i++)
		LineTo(_DC, (int)m_vQItem[i].x, (int)m_vQItem[i].y);
	LineTo(_DC, (int)m_vQItem[11].x, (int)m_vQItem[11].y);

	MoveToEx(_DC, (int)m_vQItem[17].x, (int)m_vQItem[17].y, nullptr);
	for (int i = 18; i < 23; i++)
		LineTo(_DC, (int)m_vQItem[i].x, (int)m_vQItem[i].y);
	LineTo(_DC, (int)m_vQItem[17].x, (int)m_vQItem[17].y);

}

void CBoom::WriteMatrix()
{
	D3DXMATRIX matRot, matRotX, matParents;

	D3DXMatrixTranslation(&matParents, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_fRotAngle += 5.f;
	D3DXMatrixRotationY(&matRot, D3DXToRadian(m_fRotAngle));
	matWorld = matRot*matParents;


	for (int i = 0; i < 23; ++i)
	{
		D3DXVec3TransformCoord(&m_vQItem[i], &m_vPItem[i], &matWorld);
	}
}

void CBoom::Use_Item(CObj * _pPlayer)
{
	static_cast<CPlayer*>(_pPlayer)->Add_Bomb();
	m_bDead = true;
}
