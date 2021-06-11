#pragma once
#ifndef __BOOM_H__
#define __BOOM_H__
#include "Item.h"
class CBoom :
	public CItem
{
public:
	CBoom();
	virtual ~CBoom();

	// CItem을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Render(HDC _DC) override;
	virtual void WriteMatrix() override;
	virtual void Use_Item(CObj * _pPlayer) override;
};


#endif // !__BOOM_H__
