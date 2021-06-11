#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "Obj.h"
class CItem abstract:
	public CObj
{
public:
	explicit CItem();
	virtual ~CItem();


public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() PURE;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) PURE;
	virtual void Release() override;
public :
	virtual void WriteMatrix()PURE;
	void Dir_Item();

	void Reflect_item();
	virtual void Use_Item(CObj* _pPlayer)PURE;

protected:
	bool m_bStart;
	D3DXVECTOR3 m_vPItem[50];
	D3DXVECTOR3 m_vQItem[50];
	float m_fRotAngle;
	bool m_bReflect;
	CObj* m_pPlayer;
};


#endif // !__ITEM_H__
