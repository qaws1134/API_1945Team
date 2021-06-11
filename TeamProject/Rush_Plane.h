#pragma once
#include "Monster.h"
class CRush_Plane final :
	public CMonster
{
private:

public:
	explicit CRush_Plane();
	virtual ~CRush_Plane();


public :
	// CMonster을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Ai_Pattern() override;
	virtual void WriteMatrix(float _fRotAngle) override;
	virtual void Release() override;

private:
	bool m_bBulletOn;
	bool m_bInitDir;

	// CMonster을(를) 통해 상속됨

};

