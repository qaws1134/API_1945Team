#pragma once
#ifndef __TOWERCANNON_H__
#define __TOWERCANNON_H__
#include "Monster.h"
class CTowerCannon final :
	public CMonster
{
public:
	explicit CTowerCannon();
	virtual ~CTowerCannon();

	// CMonster을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Ai_Pattern() override;
	virtual void Render(HDC _DC)override;
	virtual void WriteMatrix(float _fRotAngle) override;
};


#endif // !__TOWERCANNON_H__
