#pragma once
#include "Monster.h"
class CPosinCannon :
	public CMonster
{
public:
	CPosinCannon();
	virtual ~CPosinCannon();
	
public :
	// CMonster을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Ai_Pattern() override;
	virtual void Render(HDC _DC)override;
	virtual void WriteMatrix(float _fRotAngle) override;
public:
	void Set_Attack(bool _bAttack) { m_bAttack = _bAttack;  m_dwExitTime = GetTickCount(); };
	
	int m_iBulletCount;
	bool m_bAttack;


};

