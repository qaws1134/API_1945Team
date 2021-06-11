#pragma once
#ifndef __ENUM_H__
#define __ENUM_H__

namespace RENDERID
{
	enum ID { BACKGROUND, OBJECT, EFFECT, UI, END };
}

namespace OBJID
{

	enum ID { PLAYER, MONSTER, BULLET, M_BULLET, ITEM, STATE, EFFECT, SHIELD, UI, END };
}

namespace M_ANGLE
{
	enum DIRANGLE { IDLE, LEFT, RIGHT, UP, DOWN, DOWN_LEFT, DOWN_RIGHT, UP_LEFT, UP_RIGHT,END };
}


#endif