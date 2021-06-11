#pragma once
#ifndef __POWER_PLANE_H__
#define __POWER_PLANE_H__

#include "Monster.h"
// 파워를 주는 비행기 4마리 연속 등장
class CPower_Plane final:
	public CMonster
{
public:
	explicit CPower_Plane();
	virtual ~CPower_Plane();

public :
	virtual void Initialize() override;
	virtual void Ai_Pattern() override;
	virtual void WriteMatrix(float _fRotAngle) override;
	virtual void Dir_Plane(bool _bWalk_Out) override;
	virtual void Release() override;

private:
	bool m_bTurn;



	// CMonster을(를) 통해 상속됨

	// CMonster을(를) 통해 상속됨
};

#endif // !POWER_PLANE_H__
