#pragma once
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	//ผ๖มควิ
	static bool Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src, bool Player_Bullet);

};

