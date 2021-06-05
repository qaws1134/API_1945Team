#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"

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
		for (auto& pObj : m_listRender[i])
			pObj->Render(_DC);

		m_listRender[i].clear();
	}
}

void CObjMgr::Release()
{
}

void CObjMgr::Delete_ObjID(OBJID::ID _eID)
{
}
