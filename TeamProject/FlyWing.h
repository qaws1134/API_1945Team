#pragma once
#ifndef __FLYWING_H__
#define __FLYWING_H__
#include "Monster.h"
class CFlyWing :
	public CMonster
{
public:
	explicit CFlyWing();
	virtual ~CFlyWing();

public :
	// CMonster을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Ai_Pattern() override;
	virtual void WriteMatrix(float _fRotAngle) override;
	virtual void Dir_Plane(bool _bWalk_Out) override;
};


#endif // !__FLYWING_H__
