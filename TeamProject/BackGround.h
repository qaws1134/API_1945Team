#pragma once
#include "Obj.h"
class CBackGround :
	public CObj
{
public:
	CBackGround();
	virtual ~CBackGround();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Draw_Road(HDC _DC);
public:
	void Update_Road();

public:
	void Draw_Road_1(HDC _DC);
	void Draw_Road_2(HDC _DC);

	int i_YMove;
	int i_YMove2;

	int i_YScroll;

	int m_iCurRand;

};

