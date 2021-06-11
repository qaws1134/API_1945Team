#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "Effect.h"
#include "Bullet.h"
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}



bool CCollisionMgr::Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src, bool Player_Bullet) //  pDst -> Object, pSrc -> Bullet
{
	bool Collision_Check = false;
	RECT rc = {};
	for (auto& pDst : _Dst)
	{
		for (auto& pSrc : _Src)
		{
			if (IntersectRect(&rc, &pDst->Get_Rect(), &pSrc->Get_Rect()))
			{
				Collision_Check = true;
				pDst->Set_Hp();
				pSrc->Set_Dead();

				if (Player_Bullet)
				{
					CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CEffect>::Create(pSrc->Get_Info().vPos, pSrc->Get_Info().vDir), OBJID::EFFECT);
				}
				if (CObjMgr::Get_Instance()->Get_Player() == pDst) // 플레이어
				{
					return Collision_Check; // 바로 종료
				}
			}
		}
	}

	return Collision_Check;
}
