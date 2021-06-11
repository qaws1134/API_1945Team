#pragma once
#ifndef __POWER_H__
#define __POWER_H__
#include "Item.h"
class CPower final:
	public CItem
{
public:
	explicit CPower();
	virtual ~CPower();

	// CItem을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Render(HDC _DC) override;
	virtual void WriteMatrix() override;


	// CItem을(를) 통해 상속됨
	virtual void Use_Item(CObj* _pPlayer) override;

};


#endif // !__POWER_H__
