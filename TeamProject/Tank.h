#pragma once
#ifndef __TANK_H__
#define __TANK_H__

#include "Monster.h"
class CTank final :
	public CMonster
{
public:
	explicit CTank();
	virtual ~CTank();
public :
	// CMonster을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Render(HDC _DC);
	virtual void Ai_Pattern() override;
	virtual void WriteMatrix(float _fRotAngle) override;
	virtual void Dir_Plane(bool _bWalk_Out) override;

private:
	D3DXVECTOR3 m_vDir_Posin;
};


#endif // !__TANK
