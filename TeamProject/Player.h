#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	void Key_Check();
	void State_Change();

private:
	template <typename T>
	CObj* Create_Bullet(float _Angle)
	{
		return CAbstractFactory<T>::Create((float)m_tInfo.fX, (float)(m_tInfo.fY - m_tInfo.iCY), _Angle);
	}
private:
	float			m_fPosinAngle;
};

