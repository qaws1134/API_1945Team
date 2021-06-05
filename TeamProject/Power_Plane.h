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
	virtual void WriteMatrix() override;

};

#endif // !POWER_PLANE_H__
