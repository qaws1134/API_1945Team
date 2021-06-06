#pragma once

#ifndef __ABSTRACTFACTORY_H__
#define __ABSTRACTFACTORY_H__

class CObj;
template <typename T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _x, float _y)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);

		return pObj;
	}

	static CObj* Create(float _x, float _y, float _fAngle)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_x, _y);
		pObj->Initialize();
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
	static CObj* Create(float _x, float _y, D3DXVECTOR3 _vDir)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		pObj->Set_Dir(_vDir);
		return pObj;
	}
	static CObj* Create(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vDir)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Dir(_vDir);
		pObj->Set_Pos(_vPos.x, _vPos.y);
		return pObj;
	}
	static CObj* Create(CObj* _pTarget)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Target(_pTarget);

		return pObj;
	}
};

#endif