#pragma once
#ifndef __TRAINBOSS_H__
#define __TRAINBOSS_H__

#include "Monster.h"
class CTrainBoss final:
	public CMonster
{
public:
	explicit CTrainBoss();
	virtual ~CTrainBoss();

public :
	// CMonster을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Ai_Pattern() override;
	virtual void WriteMatrix(float _fRotAngle) override;
	virtual void Render(HDC _DC);
	virtual void Release() override;

	//위치,각도, 패턴넘버, 총알 타입, 개수, 간격

	void CreatePatternBullet(D3DXVECTOR3 _vPos, float _fAngle, int _PatternNum, int _iBulletType, float _fOffset);
	


private:
	void Begin();
	void AttPattern();
	void InitPattern();
private:


	D3DXVECTOR3 m_tPosin[2];


	bool m_bBegin;	//시작
	bool m_bBegin2;
	bool m_bPatternOn;	//패턴 입력을 안받음
	DWORD m_dwPatternTime;
	CObj* Cannon[2];

	float m_fPatternAngle;

	int m_iPatternTime;
	int m_iPatternNum;

	int m_iPrePatternNum;
	int m_iCount;

	// CMonster을(를) 통해 상속됨

};


#endif // !__TRAINBOSS_H__
