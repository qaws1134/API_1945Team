#include "stdafx.h"
#include "Power_Plane.h"


CPower_Plane::CPower_Plane()
{
}


CPower_Plane::~CPower_Plane()
{
}

void CPower_Plane::Initialize()
{
	//»ý±è»õ
	//ÃÑ¾Ë ¼±ÅÃ
	m_eRenderID = RENDERID::OBJECT;
	D3DXMatrixIdentity(&matWorld);
	m_tInfo.vSize = { 100.f,100.f,0.f };



	m_fSpeed = 5.f;
}

void CPower_Plane::Ai_Pattern()
{

}

void CPower_Plane::WriteMatrix()
{
}

