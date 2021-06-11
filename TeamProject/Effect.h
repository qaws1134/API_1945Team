#pragma once
#include "Obj.h"
class CEffect :
	public CObj
{
public:
	CEffect();
	virtual ~CEffect();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Update_Effect();
private:
	RECT	m_tRect[3];
	bool	m_bMove;
	int		m_iEffect_Size;
};

