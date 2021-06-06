#pragma once
#include "Monster.h"
class CRush_Plane final :
	public CMonster
{
private:
	enum DIRANGLE {DOWN_LEFT,DOWN_RIGHT,UP_LEFT,UP_RIGHT};
public:
	explicit CRush_Plane();
	virtual ~CRush_Plane();


public :
	// CMonster을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Ai_Pattern() override;
	virtual void WriteMatrix(float _fRotAngle) override;
	virtual void Dir_Plane(bool _bWalk_Out) override;

private:
	bool m_bBulletOn;
	float m_fTurnAngle;
	DIRANGLE m_eDir;

};

