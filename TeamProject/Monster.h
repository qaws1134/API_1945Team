#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Obj.h"
class CMonster abstract:
	public CObj
{
public:
	explicit CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize()PURE;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public :
	virtual void Ai_Pattern()PURE;
	virtual void WriteMatrix()PURE;

private:
	bool m_bTurn;	//등장 퇴장 패턴 판단
};

#endif // !__MONSTER_H__
