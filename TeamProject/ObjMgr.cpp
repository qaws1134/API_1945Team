#include "stdafx.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Player.h"
#include "Effect.h"
CObjMgr* CObjMgr::m_pInstance = nullptr;
CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		auto iter = m_listObj[i].begin();
		for (; iter != m_listObj[i].end(); )
		{
			int iEvent = (*iter)->Update();

			if (OBJ_DEAD == iEvent)
			{
				SAFE_DELETE(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Late_Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
		{
			pObj->Late_Update();

			if (m_listObj[i].empty())
				break;

			RENDERID::ID eID = pObj->Get_RenderID();

			m_listRender[eID].emplace_back(pObj);
		}
	}
}

void CObjMgr::Render(HDC _DC)
{
	for (int i = 0; i < RENDERID::END; ++i)
	{
		if (RENDERID::OBJECT == i)
			m_listRender[i].sort(CompareY<CObj*>);

		for (auto& pObj : m_listRender[i])
			pObj->Render(_DC);

		m_listRender[i].clear();
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; i++)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}
}

CObj * CObjMgr::Get_ShortTarget(INFO _INFO, OBJID::ID _eID)
{
	CObj*	pTarget = nullptr;
	float	fDis = 0.f;

	float	fX = 0.f;
	float	fY = 0.f;
	float	fDia = 0.f;

	for (auto& pDst : m_listObj[_eID])
	{
		fX = _INFO.vPos.x - pDst->Get_Info().vPos.x;
		fY = _INFO.vPos.y - pDst->Get_Info().vPos.y;
		fDia = sqrtf(fX * fX + fY * fY);

		if (fDis > fDia || !pTarget)
		{
			pTarget = pDst;
			fDis = fDia;
		}
	}

	return pTarget;
}

void CObjMgr::Collision_Update()
{
	if (!((CPlayer*)(Get_Player()))->Get_DeadMove() && CCollisionMgr::Collision_Rect(m_listObj[OBJID::PLAYER], m_listObj[OBJID::M_BULLET], false)) {}

	if (CCollisionMgr::Collision_Rect(m_listObj[OBJID::MONSTER], m_listObj[OBJID::BULLET],true) )// 몬스터와 플레이어 불렛 충돌
	{
		((CPlayer*)(Get_Player()))->Set_SuperShot_Gauge(50);
		((CPlayer*)(Get_Player()))->Set_Score(rand() % 1000);
	}

}

void CObjMgr::Delete_ObjID(OBJID::ID _eID)
{
	for_each(m_listObj[_eID].begin(), m_listObj[_eID].end(), Safe_Delete<CObj*>);
	m_listObj[_eID].clear();
}
