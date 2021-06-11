#pragma once
#ifndef __FLYWING_H__
#define __FLYWING_H__
#include "Monster.h"
class CFlyWing final:
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
	virtual void Release() override;


public :
	void CreatePatternBullet(float _fX,float _fY ,float _fAngle);
	void Set_Reverse() { m_bReverse = true; }
public :

	D3DXVECTOR3 m_vPosin[3];
	bool m_bPattern;

	bool m_bStay;
	bool m_bReverse;
	int m_bPatternCount;
	

	// CMonster을(를) 통해 상속됨

};


#endif // !__FLYWING_H__
