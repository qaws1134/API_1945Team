#include "stdafx.h"
#include "Effect.h"


CEffect::CEffect():m_bMove(false)
{
	ZeroMemory(&m_tRect, sizeof(m_tRect));

}


CEffect::~CEffect()
{
	Release();
}

void CEffect::Initialize()
{
	m_eRenderID = RENDERID::EFFECT;
	m_iEffect_Size = 10 + rand() % 15;

}
void CEffect::Set_Size(int n)
{
	m_iEffect_Size = n;
}
int CEffect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	Update_Effect();
	return OBJ_NOEVENT;
}

void CEffect::Late_Update()
{
	if (m_iEffect_Size < 0)
	{
		m_bDead = true;
	}
}

void CEffect::Render(HDC _DC)
{
	for (int i = 0; i < 3; i++)
		Ellipse(_DC, m_tRect[i].left, m_tRect[i].top, m_tRect[i].right, m_tRect[i].bottom);
}

void CEffect::Release()
{
}

void CEffect::Update_Effect()
{
	for (int i = 0; i < 3; i++)
	{
		m_tRect[i].left = (LONG)(m_tInfo.vPos.x - (m_iEffect_Size + 10) * 0.5);
		m_tRect[i].top = (LONG)(m_tInfo.vPos.y - (m_iEffect_Size + 20) * 0.5);
		m_tRect[i].right = (LONG)(m_tInfo.vPos.x - i * 10 + (m_iEffect_Size + 30) * 0.5);
		m_tRect[i].bottom = (LONG)(m_tInfo.vPos.y + (m_iEffect_Size + 40) * 0.5);
	}
	m_iEffect_Size -= 3;
}
