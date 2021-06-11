#include "stdafx.h"
#include "BackGround.h"


CBackGround::CBackGround()
{
}


CBackGround::~CBackGround()
{
	Release();
}

void CBackGround::Initialize()
{
	m_eRenderID = RENDERID::OBJECT;

	i_YScroll = 800;
	m_iCurRand = 1;

	i_YMove = -0;
	i_YMove2 = -10000;
}

int CBackGround::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	Update_Road();
	return OBJ_NOEVENT;
}

void CBackGround::Late_Update()
{
}

void CBackGround::Render(HDC _DC)
{
	Draw_Road(_DC);
}

void CBackGround::Release()
{
}


void CBackGround::Draw_Road(HDC _DC)
{

	Draw_Road_1(_DC);
	Draw_Road_2(_DC);
}

void CBackGround::Update_Road()
{
	if (i_YScroll >= 800)
	{ 
			if (m_iCurRand == 1)
			{
				m_iCurRand = 2;
				i_YMove = -800;
			}
			else if (m_iCurRand == 2)
			{
				m_iCurRand = 1;
				i_YMove2 = -800;
			}

			i_YScroll = 0;
	}
	i_YScroll += 10;
	i_YMove += 10;
	i_YMove2 += 10;

}

void CBackGround::Draw_Road_1(HDC _DC)
{
	int n1 = 230;
	int n2 = 0;
	// 그림3
	for (int j = 0; j < 2; j++)
	{
		//일반선 선 한줄(세로)
		MoveToEx(_DC, n1 + 500 + 40 * j, 0 + i_YMove + n2, nullptr);
		LineTo(_DC, n1 + 500 + 40 * j, 800 + i_YMove + n2);

		MoveToEx(_DC, n1 + 508 + 40 * j, 0 + i_YMove + n2, nullptr);
		LineTo(_DC, n1 + 508 + 40 * j, 800 + i_YMove + n2);

		//일반선 선 한줄(세로)
		MoveToEx(_DC, n1 + 520 + 40 * j, 0 + i_YMove + n2, nullptr);
		LineTo(_DC, n1 + 520 + 40 * j, 800 + i_YMove + n2);

		MoveToEx(_DC, n1 + 528 + 40 * j, 0 + i_YMove + n2, nullptr);
		LineTo(_DC, n1 + 528 + 40 * j, 800 + i_YMove + n2);

		for (int i = 0; i < 19; i++)
		{
			// 평면선 -1
			MoveToEx(_DC, n1 + 508 + 40 * j, 50 + 40 * i + i_YMove + n2, nullptr);
			LineTo(_DC, n1 + 520 + 40 * j, 50 + 40 * i + i_YMove + n2);

			// 평면선 -1
			MoveToEx(_DC, n1 + 508 + 40 * j, 63 + 40 * i + i_YMove + n2, nullptr);
			LineTo(_DC, n1 + 520 + 40 * j, 63 + 40 * i + i_YMove + n2);
		}
	}
	

	n1 = -300;
	n2 = 0;
	// 그림3
	for (int j = 0; j < 2; j++)
	{
		//일반선 선 한줄(세로)
		MoveToEx(_DC, n1 + 500 + 40 * j, 0 + i_YMove + n2, nullptr);
		LineTo(_DC, n1 + 500 + 40 * j, 800 + i_YMove + n2);

		MoveToEx(_DC, n1 + 508 + 40 * j, 0 + i_YMove + n2, nullptr);
		LineTo(_DC, n1 + 508 + 40 * j, 800 + i_YMove + n2);

		//일반선 선 한줄(세로)
		MoveToEx(_DC, n1 + 520 + 40 * j, 0 + i_YMove + n2, nullptr);
		LineTo(_DC, n1 + 520 + 40 * j, 800 + i_YMove + n2);

		MoveToEx(_DC, n1 + 528 + 40 * j, 0 + i_YMove + n2, nullptr);
		LineTo(_DC, n1 + 528 + 40 * j, 800 + i_YMove + n2);

		for (int i = 0; i < 19; i++)
		{
			// 평면선 -1
			MoveToEx(_DC, n1 + 508 + 40 * j, 50 + 40 * i + i_YMove + n2, nullptr);
			LineTo(_DC, n1 + 520 + 40 * j, 50 + 40 * i + i_YMove + n2);

			// 평면선 -1
			MoveToEx(_DC, n1 + 508 + 40 * j, 63 + 40 * i + i_YMove + n2, nullptr);
			LineTo(_DC, n1 + 520 + 40 * j, 63 + 40 * i + i_YMove + n2);
		}
	}
}

void CBackGround::Draw_Road_2(HDC _DC)
{

	int n1 = 230;
	int n2 = 0;
	// 그림3
	for (int j = 0; j < 2; j++)
	{
		//일반선 선 한줄(세로)
		MoveToEx(_DC, n1 + 500 + 40 * j, 0 + i_YMove2 + n2, nullptr);
		LineTo(_DC, n1 + 500 + 40 * j, 800 + i_YMove2 + n2);

		MoveToEx(_DC, n1 + 508 + 40 * j, 0 + i_YMove2 + n2, nullptr);
		LineTo(_DC, n1 + 508 + 40 * j, 800 + i_YMove2 + n2);

		//일반선 선 한줄(세로)
		MoveToEx(_DC, n1 + 520 + 40 * j, 0 + i_YMove2 + n2, nullptr);
		LineTo(_DC, n1 + 520 + 40 * j, 800 + i_YMove2 + n2);

		MoveToEx(_DC, n1 + 528 + 40 * j, 0 + i_YMove2 + n2, nullptr);
		LineTo(_DC, n1 + 528 + 40 * j, 800 + i_YMove2 + n2);

		for (int i = 0; i < 19; i++)
		{
			// 평면선 -1
			MoveToEx(_DC, n1 + 508 + 40 * j, 50 + 40 * i + i_YMove2 + n2, nullptr);
			LineTo(_DC, n1 + 520 + 40 * j, 50 + 40 * i + i_YMove2 + n2);

			// 평면선 -1
			MoveToEx(_DC, n1 + 508 + 40 * j, 63 + 40 * i + i_YMove2 + n2, nullptr);
			LineTo(_DC, n1 + 520 + 40 * j, 63 + 40 * i + i_YMove2 + n2);
		}
	}
	

	n1 = -300;
	n2 = 0;
	// 그림3
	for (int j = 0; j < 2; j++)
	{
		//일반선 선 한줄(세로)
		MoveToEx(_DC, n1 + 500 + 40 * j, 0 + i_YMove2 + n2, nullptr);
		LineTo(_DC, n1 + 500 + 40 * j, 800 + i_YMove2 + n2);

		MoveToEx(_DC, n1 + 508 + 40 * j, 0 + i_YMove2 + n2, nullptr);
		LineTo(_DC, n1 + 508 + 40 * j, 800 + i_YMove2 + n2);

		//일반선 선 한줄(세로)
		MoveToEx(_DC, n1 + 520 + 40 * j, 0 + i_YMove2 + n2, nullptr);
		LineTo(_DC, n1 + 520 + 40 * j, 800 + i_YMove2 + n2);

		MoveToEx(_DC, n1 + 528 + 40 * j, 0 + i_YMove2 + n2, nullptr);
		LineTo(_DC, n1 + 528 + 40 * j, 800 + i_YMove2 + n2);

		for (int i = 0; i < 18; i++)
		{
			// 평면선 -1
			MoveToEx(_DC, n1 + 508 + 40 * j, 50 + 40 * i + i_YMove2 + n2, nullptr);
			LineTo(_DC, n1 + 520 + 40 * j, 50 + 40 * i + i_YMove2 + n2);

			// 평면선 -1
			MoveToEx(_DC, n1 + 508 + 40 * j, 63 + 40 * i + i_YMove2 + n2, nullptr);
			LineTo(_DC, n1 + 520 + 40 * j, 63 + 40 * i + i_YMove2 + n2);
		}
	}
}


